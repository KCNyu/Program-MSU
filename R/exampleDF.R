nmbr = c(2, 3, 5) 
smbl = c("aa", "bb", "cc") 
bl = c(TRUE, FALSE, TRUE) 
df1 = data.frame(nmbr,smbl, bl) 
# df - фрейм данных
head(df1)

tail(df1)


#Создание векторов id, name, age and country are vectors
#Data Frame Creation
#вектор id column, fill 1 to 3

  id <- c ( 1 : 3 )
#вектор name

  name <- c ( "Janice" , "Tommy" , "Brad" )
#вектор возраст

  age <- c ( 23 , 31 , 25 )
#Страна
country <- c ( "USA" , "Canada" , "Argentina" )
#персона
person_df <- data.frame ( id, name, age, country )
#Значение data frame
print ( person_df )

print (person_df[c(1,3),c(1,3)])
