SELECT RegionDescription,
	    FirstName,
	    LastName,
	    BirthDate
FROM (SELECT FirstName,
		    LastName,
		    BirthDate,
		    RegionId,
		    RegionDescription

        FROM Employee 
        LEFT OUTER JOIN EmployeeTerritory
        ON Employee.Id = EmployeeId
        LEFT OUTER JOIN Territory
        ON TerritoryId = Territory.Id 
        LEFT OUTER JOIN Region
        ON RegionId = Region.Id
        ORDER BY BirthDate DESC) 

GROUP BY RegionId
ORDER BY RegionId;