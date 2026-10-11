# Write your MySQL query statement below
select pr.product_id , 
IFNull(round(sum(pr.price * un.units)/ sum(un.units),2),0)as average_price 
from Prices pr
left join UnitsSold un
on pr.product_id=un.product_id
and  un.purchase_date between pr.start_date and pr.end_date
group by pr.product_id;
