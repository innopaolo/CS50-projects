SELECT title FROM movies WHERE movies.id IN
(SELECT stars.movie_id from stars WHERE stars.person_id IN
(SELECT people.id FROM people WHERE people.name = "Johnny Depp"))
AND movies.id IN
(SELECT stars.movie_id from stars WHERE stars.person_id IN
(SELECT people.id FROM people WHERE people.name = "Helena Bonham Carter"));