SELECT Id,
    OrderDate,
    
    LAG(OrderDate,1,OrderDate) 
    OVER(ORDER BY OrderDate) 
    AS PreOrderDate,
    
    ROUND(
        julianday(OrderDate)-
        julianday(
            LAG(OrderDate,1,OrderDate) 
            OVER(ORDER BY OrderDate) )
        ,2) 
    AS Differ
FROM 'Order'
WHERE CustomerID = 'BLONP'
ORDER BY OrderDate
LIMIT 10;