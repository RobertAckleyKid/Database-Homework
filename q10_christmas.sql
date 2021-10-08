SELECT 
GROUP_CONCAT(ProductName,', ') 
AS ProductNames
FROM 'Order' AS O
	LEFT OUTER JOIN OrderDetail 
	ON O.Id = OrderId 
	LEFT OUTER JOIN Product
	ON ProductId = Product.Id 
	LEFT OUTER JOIN Customer
	ON CustomerId = Customer.Id 
WHERE CompanyName = 'Queen Cozinha'
	AND o.OrderDate LIKE '%2014-12-25%'; 
