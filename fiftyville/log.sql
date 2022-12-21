-- Keep a log of any SQL queries you execute as you solve the mystery.

--the schema
.schema

--event date
SELECT description FROM crime_scene_reports WHERE street ='Humphrey Street';

--interveiews with witnesses

SELECT name FROM interviews WHERE year = 2021 AND day = 28 month = 7;

--transcrpits of the interveiws

SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

--checking the license_plates in the security logs at 10:15 to 10:25

SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND day = 28 AND month = 7 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit';

--getting names from plates on file

SELECT DISTINCT name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021 AND day = 28 AND month = 7 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit';

--checking a bank account from the bank on legget street for withdraws on the day of the inceddent

SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";


--checking airport logs for flights leaving the next day and from fiftvilles airport "07/29/2021" ordered by first to last
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = ( SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id =
( SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour, minute LIMIT 1);



--checking phone logs

SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;


--seeing where the theif went from fiftyville

SELECT city FROM airports
WHERE id = ( SELECT destination_airport_id FROM flights WHERE day = 29 AND year = 2021 AND month = 7 AND origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour, minute);

--finding the theif"s phone number

SELECT phone_number FROM people WHERE name = "Bruce";

--checking to see who called the theif at thetime of the inccednt (robin)

SELECT name FROM people WHERE phone_number =
(SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND caller = "(367) 555-5533" AND duration = < 60);

