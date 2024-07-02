SELECT DISTINCT (title)
  FROM movies
       INNER JOIN stars
          ON movies.id = stars.movie_id
  WHERE stars.person_id IN
        ((SELECT id
            FROM people
            WHERE name = "Johnny Depp"),
         (SELECT id
            FROM people
            WHERE name = "Helena Bonham Carter"))
  GROUP BY title HAVING COUNT(*) = 2;
