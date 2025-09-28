
use IndividualWorkDB

--1 Select all the films where Christopher Nolan is a contributor
select distinct *
from Films
where FilmId in 
	(select Film 
	from Contributions
	where Person =
		(select PersonId 
		from Persons
		where CONCAT(FirstName, ' ', LastName) = 'Christopher Nolan'))

--2 Select all reviews of a film
select * 
from Reviews
where Film = 
	(select FilmId 
	from Films
	where FilmName = 'Inception')

--3 Select all films with ammount of their reviews and rating as HIGH, LOW, MEDIUM
select 
	FilmName,
    COUNT(ReviewId) AS ReviewCount, 
    case 
        when AVG(Rating) < 2.5 then 'LOW' 
        when AVG(Rating) < 4 then 'MEDIUM'
        else 'HIGH'
	end as RatingCategory
from Reviews
join Films on Film = FilmId
group by FilmName

--4 Count films by countries
select 
	CountryName, 
	COUNT(Films.FilmId) as FilmCount
from Countries
join CinemaCompanies on Countries.CountryId = CinemaCompanies.Country
join Films on CinemaCompanies.CompanyId = Films.Company
group by Countries.CountryName

--5 Select top 5 most high rated films in USA
select top 5 
	Films.FilmName, 
	avg(Reviews.Rating)
from Films
join CinemaCompanies on CinemaCompanies.CompanyId = Films.Company
join Countries on Countries.CountryId = CinemaCompanies.Country
join Reviews on Reviews.Film = Films.FilmId
where Countries.CountryName = 'USA'
group by 
	Films.FilmName, 
	Countries.CountryName
order by AVG(Rating) desc

--6. Selecty films where was more than 1 director
select 
	FilmName,
	COUNT(Contributions.Person) as Directors
from Films
join Contributions on Contributions.Film = Films.FilmId
where Contributions.Role = 1
group by Films.FilmName
having count (Contributions.Person) > 1

--7 Select top 5 users with most of the written reviews
select top 5
    Users.UserName,
    COUNT(Reviews.ReviewId) as ReviewCount
from Users
join Reviews on Reviews.Author = Users.UserId
group by Users.UserName
order by ReviewCount desc

--8 Select films along with the count of unique countries represented by individuals who contributed to the movies as Actors
select 
    Films.FilmName,
    count(distinct Persons.Country) as CountryCount
from Films
join Contributions on Contributions.Film = Films.FilmId
join Persons on Persons.PersonId = Contributions.Person
where Contributions.Role = 2  
group by Films.FilmName
having count(distinct Persons.Country) > 1

--9 Count films by genres
select 
    Genres.GenreName,
    COUNT(Films.FilmId) as FilmCount
from Films
join Genres on Genres.GenreId = Films.Genre
group by Genres.GenreName

--10 Select average rating of films by genres
select 
	Genres.GenreName, 
	AVG(Reviews.Rating) as AverageRating 
from Films 
join Reviews on Films.FilmId = Reviews.Film 
join Genres on Films.Genre = Genres.GenreId 
group by Genres.GenreName

--views

--1 Select film details
--select * from FilmDetails
--drop view FilmDetails

create view FilmDetails as
select 
	f.FilmId, 
	f.FilmName, 
	c.CompanyName, 
	g.GenreName
from Films f
join CinemaCompanies c on f.Company = c.CompanyId
join Genres g on f.Genre = g.GenreId

--2 Select rivew details
--select * from ReviewDetails
--drop view ReviewDetails

create view ReviewDetails as
select 
	r.ReviewId, 
	f.FilmName, 
	u.UserName as ReviewerName,
	r.Rating
from Reviews r
join Films f on r.Film = f.FilmId
join Users u on r.Author = u.UserId

--3 Select contributions along with people and their role
--select * from PersonContributions
--drop view PersonContributions

create view PersonContributions as
select 
	p.FirstName, 
	p.LastName, 
	f.FilmName, 
	r.RoleName
from Contributions c
join Persons p on c.Person = p.PersonId
join Films f on c.Film = f.FilmId
join Roles r on c.Role = r.RoleId

--4 Select top rated films with rating > 4.5
--select * from TopRatedFilms
--drop view TopRatedFilms

create view TopRatedFilms as
select 
	f.FilmName, 
	AVG(r.Rating) as AverageRating
from Reviews r
join Films f on r.Film = f.FilmId
group by f.FilmName
having AVG(r.Rating) > 4.5

--5 Select films with companies and countries
--select * from FilmCountries
--drop view FilmCountries

create view FilmCountries as
select f.FilmName, c.CountryName
from Films f
join CinemaCompanies cc on f.Company = cc.CompanyId
join Countries c on cc.Country = c.CountryId