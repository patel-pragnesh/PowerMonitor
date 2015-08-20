//
//  TimeSlotCell.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 08/06/2015.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit

class TimeSlotCell: UITableViewCell
{
	var timeSlotId: Int!
	@IBOutlet weak var onTime: UILabel!
	@IBOutlet weak var offTime: UILabel!
}