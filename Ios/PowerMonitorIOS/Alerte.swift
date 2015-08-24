//
//  Alerte.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 12/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

struct Alerte
{
	//var id: Int
	//var unitId: Int
	//var value: Double
}

/*
** Extract alertes data and put it into a Alertes array
*/
func generateAlertesListFromJSON(alertesJSON: JSON) -> [Alerte]
{
	var alertes = [Alerte]()

	for (index: String, alerteJSON: JSON) in alertesJSON
	{
		var alerte: Alerte

		alerte = generateAlerteFromJSON(alerteJSON)
		alertes.append(alerte)
	}
	return alertes
}

/*
** Extract alerte data and put it into a Alerte object
*/
func generateAlerteFromJSON(alerte: JSON) -> Alerte
{
	var alerte: Alerte

	alerte = Alerte(/* //TODO */)
	return alerte
}
