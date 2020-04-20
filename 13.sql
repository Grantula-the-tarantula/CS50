SELECT DISTINCT people.name
FROM people
WHERE name IS NOT 'Kevin Bacon'
AND id IN
(SELECT person_id from stars WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name IS 'Kevin Bacon' AND birth = 1958)))