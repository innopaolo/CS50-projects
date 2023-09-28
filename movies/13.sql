SELECT name FROM people WHERE id IN
(SELECT stars.person_id FROM stars WHERE stars.movie_id IN
(SELECT stars.movie_id FROM stars, people
WHERE stars.person_id = people.id
AND people.name = "Kevin Bacon"
AND birth = 1958))
AND name != "Kevin Bacon";
