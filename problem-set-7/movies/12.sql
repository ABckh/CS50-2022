SELECT title FROM movies, stars, people 
WHERE movies.id = stars.movie_id AND stars.person_id = people.id 
AND name = "Johnny Depp" AND title IN 
(SELECT title FROM movies, stars, people 
  WHERE movies.id = stars.movie_id 
  AND stars.person_id = people.id 
  AND name = "Helena Bonham Carter");
