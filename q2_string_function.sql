SELECT DISTINCT 
ShipName, 
substr(shipName,0,instr(shipName,'-')) AS Pre
FROM 'Order' 
WHERE ShipName LIKE '%-%'
ORDER BY ShipName;