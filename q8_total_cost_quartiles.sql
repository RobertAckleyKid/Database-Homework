SELECT CompanyName,
    CustomerId,
    printf("%.2f",expenditure) 
        AS expenditure
FROM
  (SELECT 
    IFNULL(CompanyName, "MISSING_NAME") 
        AS CompanyName, 
    CustomerId, 
    expenditure, 
    NTILE(4) OVER(
            ORDER BY expenditure) 
            AS Quartile 
    FROM 

    (SELECT "Order".CustomerId, 
            SUM((UnitPrice*Quantity)) 
                AS expenditure
    FROM 
        "Order" 
        LEFT OUTER JOIN OrderDetail 
            ON "Order".Id = OrderDetail.OrderId 
            GROUP BY CustomerId
    )
        LEFT OUTER JOIN Customer 
            ON CustomerId = Customer.Id
    
  )
WHERE Quartile=1;