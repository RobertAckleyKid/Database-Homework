SELECT Id, ShipCountry,
    CASE
    WHEN ShipCountry IN ('USA','Mexico','Canada') 
        THEN 'NorthAmerica' 
    ELSE 'OtherPlcae'
    END AS NAorNot
FROM 'Order'
WHERE Id>=15445
ORDER BY Id
LIMIT 20;