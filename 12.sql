SELECT movies.title
FROM ((stars
JOIN people ON stars.person_id = people.id)
JOIN movies ON stars.movie_id = movies.id)
WHERE people.name = 'Johnny Depp'
INTERSECT
SELECT movies.title
FROM ((stars
JOIN people ON stars.person_id = people.id)
JOIN movies ON stars.movie_id = movies.id)
WHERE people.name = 'Helena Bonham Carter';
