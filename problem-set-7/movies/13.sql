SELECT COUNT(DISTINCT(name)) FROM people
JOIN stars ON stars.person_id=people.id
JOIN movies ON stars.movie_id=movies.id
WHERE movies.id IN
(SELECT movies.id FROM movies
JOIN people ON stars.person_id=people.id
JOIN stars ON stars.movie_id=movies.id
WHERE people.name="Kevin Bacon"
AND birth=1958)
AND name != "Kevin Bacon";
