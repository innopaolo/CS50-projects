-- Log of SQL queries to solve the mystery
-- Open a text file to copy relevant details to

-- Search the reports using the first lead
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = "Humphrey Street";

-- Find the three interviewees
SELECT name
FROM interviews
WHERE month = 7 AND day = 28;

-- Check the bakery security logs
-- Check plates against the crime timeframe
SELECT hour, minute, activity, license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28;

-- Check license plates against the people table
-- Create a list of suspects and their passport numbers
SELECT name, passport_number, license_plate
FROM people
WHERE license_plate IN ("5P2BI95", "94KL13X", "6P58WS2", "4328GD8",
                        "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55");

-- Suspicious suspects: Vanessa, Barry, Bruce, Iman, Sofia,
-- Luca, Diana, Kelsey

-- Check the ATM table for transactions on the day of the crime
-- Take note of the bank accounts that withdrew large amounts
SELECT *
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_locations = "Leggett Street";

-- Check names of people who hold these bank accounts
-- Update suspect list with common names
SELECT name, account_number
FROM people, bank_accounts
WHERE bank_accounts.person_id = people.id
AND bank_accounts.account_number IN (28500762, 28296815, 76054385, 49610011,
                                     16153065, 25506511, 81061156, 26013199);

-- Updated suspect list: Bruce, Iman, Luca, Diana

-- Check short phone calls on the day of the crime
-- Cross reference suspect list to tease out accomplice
SELECT caller, p1.name, receiver, p2.name, duration
FROM phone_calls
JOIN people AS p1 ON phone_calls.caller = p1.phone_number
JOIN people AS p2 ON phone_calls.receiver = p2.phone_number
WHERE month = 7 AND day = 28
AND duration < 60;

-- So far, the common names that show up from all three clues:
-- Bruce and Diana
-- Bruce called Robin, Diana called Philip

-- Find Fiftyville's airport ID
SELECT *
FROM airports;

-- Check for passengers from flights leaving the day after the crime
-- If both suspects show up, find which one flew earlier
SELECT flights.id, passengers.passport_number, name, hour, minute
FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
WHERE month = 7 AND day = 29
AND origin_airport_id = 8;

-- Confirmed: Bruce is a hardened rubber duckie thief
-- Robin is his miserable wretch of an accomplice

-- Find their destination so that they may be apprehended by the CS50 Intergalactic Police Force
SELECT city
FROM airports
WHERE id IN
      (SELECT destination_airport_id
       FROM flights
       WHERE flights.id = 36);

-- Bampot Bruce's destination: New York City!