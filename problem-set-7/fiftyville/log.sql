-- Keep a log of any SQL queries you execute as you solve the mystery.

-- to find what scene reports were made at this day at this street;
  SELECT * 
  FROM crime_scene_reports 
  WHERE street = "Humphrey Street" 
    AND year = 2021 
    AND month = 7 
    AND day = 28; 
-- We get the information about bakery and time of crime is 10.15AM 

  SELECT * 
  FROM interviews 
  WHERE year = 2021 
    AND month = 7 
    AND day = 28;

-- we've read 3 interviews and find the information about
-- 1) Bakery parking lot

  SELECT name 
  FROM people
  JOIN bakery_security_logs 
    ON people.license_plate = bakery_security_logs.license_plate
  WHERE bakery_security_logs.year = 2021
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute >= 15
    AND bakery_security_logs.minute <= 25
    AND bakery_security_logs.activity = "exit";
-- Vanessa
-- Bruce
-- Barry
-- Luca
-- Sofia
-- Iman
-- Diana
-- Kelsey

-- 2) ATM at Legget street
  SELECT name 
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
  JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
  WHERE atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_transactions.atm_location = 'Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw';
-- Bruce
-- Diana
-- Brooke
-- Kenny
-- Iman
-- Luca
-- Taylor
-- Benista

-- 3) Flight put of the Fiftyville
-- Caller  
  SELECT name, phone_calls.receiver
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.caller
  WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60;
-- Sofia|(996) 555-8899
-- Kelsey|(892) 555-8872
-- Bruce|(375) 555-8161
-- Kelsey|(717) 555-1342
-- Taylor|(676) 555-6554
-- Diana|(725) 555-3243
-- Carina|(910) 555-3251
-- Kenny|(066) 555-9701
-- Benista|(704) 555-2131

-- Receiver 
  SELECT name, phone_calls.receiver
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
  WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60;
-- Jack|(996) 555-8899
-- Larry|(892) 555-8872
-- Robin|(375) 555-8161
-- Melissa|(717) 555-1342
-- James|(676) 555-6554
-- Philip|(725) 555-3243
-- Jacqueline|(910) 555-3251
-- Doris|(066) 555-9701
-- Anna|(704) 555-2131

-- Flight

  SELECT city, flights.hour, flights.minute 
  FROM airports 
  JOIN flights 
    ON airports.id = flights.destination_airport_id  
  WHERE flights.origin_airport_id = (
    SELECT id 
    FROM airports
    WHERE city = "Fiftyville"
  )
    AND flights.year = 2021
    AND flights.month = 7
    AND flights.day = 29
  ORDER BY flights.hour, flights.minute;

-- LaGuardia Airport|New York City|8|20
-- O'Hare International Airport|Chicago|9|30
-- San Francisco International Airport|San Francisco|12|15
-- Tokyo International Airport|Tokyo|15|20
-- Logan International Airport|Boston|16|0
-- The erliest flight tomorrow is to New York


  SELECT name
  FROM people
  JOIN passengers
    ON people.passport_number = passengers.passport_number
  JOIN flights
    ON passengers.flight_id = flights.id
  JOIN airports
    ON flights.destination_airport_id = airports.id
    WHERE flights.origin_airport_id= (
      SELECT id
      FROM airports
      WHERE city = "Fiftyville")
    AND flights.year = 2021
    AND flights.month = 7
    AND flights.day = 29
    AND flights.hour = 8
    AND flights.minute = 20; 
-- Doris
-- Sofia
-- Bruce
-- Edward
-- Kelsey
-- Taylor
-- Kenny
-- Luca

-- Bruce is the thief, because he is in all lists
-- Robin is accomplience, because Bruce called him and he bought tickets for Bruce
-- Bruce escaped to New York
