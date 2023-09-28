SELECT title, year
FROM movies
WHERE title LIKE "%harry potter and the%" OR title LIKE "%harry potter:%"
ORDER BY year;