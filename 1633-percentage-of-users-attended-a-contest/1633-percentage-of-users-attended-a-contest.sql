# Write your MySQL query statement below
select contest_id , ROUND(COUNT(user_id) * 100.0 / (SELECT COUNT(*) FROM Users), 2) AS percentage
from Register
group by contest_id
order by percentage  desc, contest_id asc;

