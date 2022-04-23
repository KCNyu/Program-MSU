package jms.client;

import jms.command.SerializableCommand;
import jms.command.SerializableReturn;
import org.apache.activemq.ActiveMQConnection;
import org.apache.activemq.ActiveMQConnectionFactory;

import javax.jms.*;
import java.util.Random;

public class Client {
    public Session createSession() throws JMSException {
        ActiveMQConnectionFactory connectionFactory = new ActiveMQConnectionFactory("tcp://185.188.181.184:8080");
        connectionFactory.setTrustAllPackages(true);

        ActiveMQConnection connection = (ActiveMQConnection) connectionFactory.createConnection();
        connection.start();
        return connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
    }

    public MessageProducer createProducer(Session session) throws JMSException {
        Destination destination = session.createTopic("COMMANDS");

        MessageProducer producer = session.createProducer(destination);
        producer.setDeliveryMode(DeliveryMode.PERSISTENT);
        return producer;
    }

    public MessageConsumer createConsumer(Session session) throws JMSException {
        Destination destination = session.createTopic("RETS");

        MessageConsumer consumer = session.createConsumer(destination);
        return consumer;
    }

    public SerializableReturn sendMessage(SerializableCommand command, Session session, MessageProducer producer, MessageConsumer consumer) throws JMSException {
        ObjectMessage objectMessage = session.createObjectMessage(command);
        producer.send(objectMessage);

        while (true) {
            Message message = consumer.receive();
            if (message instanceof ObjectMessage) {
                Object ret = ((ObjectMessage) message).getObject();
                SerializableReturn retCommand = (SerializableReturn) ret;
                System.out.println(retCommand);
                if (retCommand.carIndex == command.carIndex) {
                    return retCommand;
                }
            }
        }
    }

    public static void main(String[] args) {
        Random random = new Random();
        int carIndex = random.nextInt(Integer.MAX_VALUE);
        SerializableCommand command = new SerializableCommand(carIndex, "CREATECAR", "");
        Client client = new Client();
        try {
            Session session = client.createSession();
            MessageProducer producer = client.createProducer(session);
            MessageConsumer consumer = client.createConsumer(session);
            SerializableReturn ret_create = client.sendMessage(command, session, producer, consumer);
            System.out.println(ret_create);
            carIndex = (Integer) ret_create.ret;
            client.sendMessage(new SerializableCommand(carIndex, "SETNAME", "cxd"), session, producer, consumer);
            String [] directions = {"UP", "DOWN", "LEFT", "RIGHT"};
            String direction = "DOWN";
            while (true) {
                SerializableReturn ret = client.sendMessage(new SerializableCommand(carIndex, direction, "1"), session, producer, consumer);
                System.out.println("ret: " + ret);
                if (!(boolean)ret.ret){
                    direction = directions[random.nextInt(4)];
                }
            }
        } catch (JMSException e) {
            e.printStackTrace();
        }

    }
}