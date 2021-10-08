SELECT CategoryName,
    COUNT(CategoryName),
    ROUND(AVG(UnitPrice),2),
    MIN(UnitPrice),
    MAX(UnitPrice),
    SUM(UnitsOnOrder)
FROM Category LEFT OUTER JOIN Product
ON Category.Id = CategoryId
GROUP BY Category.Id 
HAVING COUNT(CategoryName)>10 
ORDER BY CategoryId;


