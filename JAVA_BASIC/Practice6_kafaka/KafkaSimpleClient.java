package kafka;

import car.CarServer;
import car.command.Command;
import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;
import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.apache.kafka.common.protocol.types.Field;
import org.apache.kafka.common.serialization.IntegerDeserializer;
import org.apache.kafka.common.serialization.IntegerSerializer;
import org.apache.kafka.common.serialization.StringDeserializer;
import org.apache.kafka.common.serialization.StringSerializer;

import javax.print.attribute.standard.DialogOwner;
import java.nio.file.LinkOption;
import java.time.Duration;
import java.util.Arrays;
import java.util.Properties;
import java.util.Random;

import static car.BasicCarServer.maxCarSecondsDonNotMove;

/**
 * @author : Alex
 * @created : 02.05.2021, воскресенье
 **/
public class KafkaSimpleClient implements Runnable {

    final KafkaProducer<Integer, String> producer;
    final KafkaConsumer<Integer, String> consumer;

    static final String user = "admin";
    static final String password = "admin-secret";
    static final String broker = "185.188.181.184:8080";
    public static final String commandChannel = "COMMANDS";
    public static final String retChannel = "RETS";
    private final String consumerGroup;

    private Properties prepareProperties(String username, String password, String brokers, String consumerGroup) {
        String jaasTemplate = "org.apache.kafka.common.security.plain.PlainLoginModule required username=\"%s\" password=\"%s\";";
        String jaasCfg = String.format(jaasTemplate, username, password);
        String valueSerializer = StringSerializer.class.getName();
        String valueDeserializer = StringDeserializer.class.getName();

        String keySerializer = IntegerSerializer.class.getName();
        String keyDeserializer = IntegerDeserializer.class.getName();


        Properties properties = new Properties();
        properties.put("bootstrap.servers", brokers);
        properties.put("group.id", consumerGroup);
        properties.put("enable.auto.commit", "true");
        properties.put("auto.commit.interval.ms", "1000");
        properties.put("auto.offset.reset", "earliest");
        properties.put("session.timeout.ms", "30000");
        properties.put("key.deserializer", keyDeserializer);
        properties.put("value.deserializer", valueDeserializer);
        properties.put("key.serializer", keySerializer);
        properties.put("value.serializer", valueSerializer);
        properties.put("security.protocol", "SASL_PLAINTEXT");
        properties.put("sasl.mechanism", "PLAIN");
        properties.put("sasl.jaas.config", jaasCfg);
        return properties;
    }

    public KafkaSimpleClient(String group) {
        this.consumerGroup = group;
        Properties properties = prepareProperties(user, password, broker, consumerGroup);
        producer = new KafkaProducer<>(properties);
        consumer = new KafkaConsumer<>(properties);
        consumer.subscribe(Arrays.asList(retChannel));
    }

    public String sendCommand(int carIndex, String command) {
        producer.send(new ProducerRecord<Integer, String>(commandChannel, carIndex, command));
        while (true) {
            ConsumerRecords<Integer, String> records = consumer.poll(Long.MAX_VALUE);
            if (records.count() > 0) {
                for (ConsumerRecord<Integer, String> record : records) {
                    if (record.key() == carIndex) {
                        System.out.println(record.key());
                        //consumer.commitSync();
                        return record.value();
                    }
                }
                consumer.commitSync();
            }
        }
        //return null;
    }

    public static void main(String[] args) throws InterruptedException {
        new Thread(new KafkaSimpleClient("LSY-3")).start();
        //new Thread(new KafkaSimpleClient("LSY-2")).start();
    }

    @Override
    public void run() {
        Random random = new Random();
        int carIndex = random.nextInt(Integer.MAX_VALUE);
        String res = sendCommand(carIndex, "CREATECAR");
        System.out.println(res);
        carIndex = Integer.parseInt(res);
        System.out.println("carIndex: " + carIndex);
        sendCommand(carIndex, "SETNAME LSY");
        String direction = "DOWN 1";
        String[] commands = {"UP 1", "DOWN 1", "LEFT 1", "RIGHT 1"};
        while (true) {
            res = sendCommand(carIndex, direction);
            System.out.println("res: " + res);
            if (res != "true") {
                direction = commands[random.nextInt(4)];
            }
        }
    }
}
