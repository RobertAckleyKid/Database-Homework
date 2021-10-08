SELECT CompanyName,
    ROUND(
    1.0*COUNT(
        CASE WHEN ShippedDate>RequiredDate 
                THEN 1 
            ELSE NULL 
        END)*100
        /COUNT('Order'.Id)
    ,2)
    as DelayPercent
FROM 'Shipper' INNER JOIN 'Order'
ON 'Shipper'.Id = 'Order'.ShipVia
GROUP BY 'Shipper'.Id
ORDER BY DelayPercent desc;