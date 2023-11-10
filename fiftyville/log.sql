-- Keep a log of any SQL queries you execute as you solve the mystery.

-- First, to assess all of the information of the crime scene, with correct date and venue
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month =7 AND day =28 AND street="Humphrey Street";
/* Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews were conducted today with three witnesses who were present at the time –
each of their interview transcripts mentions the bakery. |*/


--ok so there are 3 witnesses. Lets look at the witness accounts
SELECT name,transcript FROM interviews WHERE year = 2021 AND month =7 AND day =28;
/*| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket. |*/


--ok lets work from Ruth's information. Get car log of cars that left around 10.15am
SELECT activity,license_plate FROM bakery_security_logs WHERE year = 2021 AND month =7 AND day =28 AND hour = 10 AND minute>15 and minute<25;

--Now get the names of these people
SELECT name FROM people WHERE license_plate IN (SELECT license_plate
FROM bakery_security_logs WHERE year = 2021 AND month =7 AND day =28 AND hour = 10 AND minute>15 and minute<25);

-- Work on Eugene's information. Get the names of the people who used the ATM to withdraw money at leggett Street
SELECT name FROM people
JOIN bank_accounts ON people.id=bank_accounts.person_id
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month =7 AND day =28
AND transaction_type="withdraw" AND atm_location="Leggett Street");

--Work on Raymond's info
SELECT name FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE duration<60 AND year = 2021 AND month =7 AND day =28)
AND name IN (SELECT name FROM people
JOIN bank_accounts ON people.id=bank_accounts.person_id
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month =7 AND day =28
AND transaction_type="withdraw" AND atm_location="Leggett Street")) AND name IN
(SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month =7 AND day =28 AND hour = 10 AND minute>=15 and minute<=25));
-- Either Diana or Bruce

SELECT id,hour,minute,destination_airport_id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city="Fiftyville")
AND year = 2021 AND month =7 AND day =29 ORDER BY hour,minute LIMIT 1;

--id 36, destination is 4

SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id=36);

SELECT name FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE duration<60 AND year = 2021 AND month =7 AND day =28)
AND name IN (SELECT name FROM people
JOIN bank_accounts ON people.id=bank_accounts.person_id
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month =7 AND day =28
AND transaction_type="withdraw" AND atm_location="Leggett Street")) AND name IN
(SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month =7 AND day =28 AND hour = 10 AND minute>=15 and minute<=25) )
AND name IN (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id=36));

--IT IS BRUCE!

--Find his call receiver

SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE duration<60 AND year = 2021 AND
month =7 AND day =28 AND caller=(SELECT phone_number FROM people WHERE name="Bruce"));

-- Accomplice is Robin!

-- Find Destination City

SELECT city FROM airports WHERE id=4;
-- NYC
