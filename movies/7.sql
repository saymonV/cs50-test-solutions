SELECT movies.title, ratings.rating
  FROM ratings, movies
  WHERE ratings.movie_id = movies.id
    AND movies.year = "2010"
    AND ratings.rating IS NOT NULL
  ORDER BY rating DESC, title;