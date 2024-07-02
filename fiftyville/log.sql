-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking the Crime Scene reports
SELECT *
  FROM crime_scene_reports
  WHERE year = 2021
    AND month = 7
    AND day = 28
    AND street = "Humphrey Street";

-- Read the interviews
SELECT *
  FROM interviews
  WHERE year = 2021
    AND month = 7
    AND day = 28
    AND transcript
    LIKE "%bakery%";

-- Check for earliest flight next day from Fiftyville
SELECT id
  FROM flights
  WHERE year = 2021
    AND month = 7
    AND day = 29
    AND origin_airport_id =
        (SELECT id
           FROM airports
           WHERE city = "Fiftyville")
    ORDER BY hour, minute
    LIMIT 1;

-- Flight destination
-- New York
SELECT *
  FROM airports
  WHERE airports.id =
        (SELECT destination_airport_id
          FROM flights
          WHERE flights.id =
                (SELECT id
                   FROM flights
                   WHERE year = 2021
                     AND month = 7
                     AND day = 29
                     AND origin_airport_id =
                         (SELECT id
                            FROM airports
                            WHERE city = "Fiftyville")
                   ORDER BY hour, minute
                   LIMIT 1));

-- Flight passengers list
SELECT passengers.passport_number, people.name, people.license_plate
   FROM passengers
   INNER JOIN people
   ON passengers.passport_number = people.passport_number
   WHERE flight_id =
         (SELECT id
            FROM flights
            WHERE year = 2021
              AND month = 7
              AND day = 29
              AND origin_airport_id =
                  (SELECT id
                     FROM airports
                     WHERE city = "Fiftyville")
            ORDER BY hour, minute
            LIMIT 1);



-- Shortlist of suspects after cross-refencing passengers on earliest flight with exits from bakery in 10 minutes span after the robery
-- Bruce, Luca, Sofia, Kelsey
SELECT activity, bakery_security_logs.license_plate, hour, minute, c.name, c.phone_number
  FROM bakery_security_logs
  INNER JOIN
        (SELECT passengers.passport_number, people.name, people.license_plate, people.phone_number
           FROM passengers
           INNER JOIN people
           ON passengers.passport_number = people.passport_number
           WHERE flight_id =
                 (SELECT id
                    FROM flights
                    WHERE year = 2021
                      AND month = 7
                      AND day = 29
                      AND origin_airport_id =
                          (SELECT id
                             FROM airports
                             WHERE city = "Fiftyville")
                      ORDER BY hour, minute
                      LIMIT 1)) AS c
  ON bakery_security_logs.license_plate = c.license_plate
  WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute <= 25
    AND activity = "exit";

-- Checking which of the 4 susspects withdrew money on Leggett Street
-- Luca, Bruce
SELECT *
  FROM people
  WHERE id IN
    (SELECT person_id
       FROM bank_accounts
       WHERE account_number IN
         (SELECT atm_transactions.account_number
            FROM atm_transactions
            INNER JOIN
                (SELECT account_number
                   FROM bank_accounts
                   WHERE person_id IN
                     (SELECT id
                        FROM people
                        WHERE name = "Bruce"
                           OR name = "Luca"
                           OR name = "Kelsey"
                           OR name = "Sofia")) AS t
            ON atm_transactions.account_number = t.account_number
            WHERE year = 2021
              AND month = 7
              AND day = 28
              AND atm_location = "Leggett Street"
              AND transaction_type = "withdraw"));



-- Checking phone calls of the suspects with the accomplice
-- Only Bruce called a number
SELECT caller, people.name, receiver
  FROM phone_calls
  INNER JOIN people
  ON phone_calls.caller = people.phone_number
  WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
    AND people.phone_number IN
        (SELECT phone_number
           FROM people
           WHERE name = "Bruce"
           OR name = "Luca");

-- Number turns out to be Robin's
SELECT *
  FROM people
  WHERE phone_number =
        (SELECT receiver
           FROM phone_calls
           INNER JOIN people
           ON phone_calls.caller = people.phone_number
           WHERE year = 2021
             AND month = 7
             AND day = 28
             AND duration < 60
             AND people.phone_number IN
                 (SELECT phone_number
                    FROM people
                    WHERE name = "Bruce"
                    OR name = "Luca"));


































