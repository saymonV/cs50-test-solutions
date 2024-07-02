SELECT DISTINCT(name)
  FROM people
  WHERE people.id IN
        (SELECT person_id
            FROM directors
            WHERE movie_ID IN
                  (SELECT movie_id
                     FROM ratings
                     WHERE rating >= 9.0))
  ORDER BY people.name;