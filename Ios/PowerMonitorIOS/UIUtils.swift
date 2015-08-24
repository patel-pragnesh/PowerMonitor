//
//  UIUtils.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 07/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit

typealias alertViewContent = (title: String, msg: String, btn: String)
typealias confirmationContent = (title: String, msg: String, btn1: String, btn2: String)

/*
** Create UIColor from hex value
*/
func		UIColorFromHex(rgbValue: UInt) -> UIColor
{
	return UIColor(
		red: CGFloat((rgbValue & 0xFF0000) >> 16) / 255.0,
		green: CGFloat((rgbValue & 0x00FF00) >> 8) / 255.0,
		blue: CGFloat(rgbValue & 0x0000FF) / 255.0,
		alpha: CGFloat(1.0)
	)
}

/*
** Generate an alertview for the sender
*/
func popAlertView(sender: AnyObject, content: alertViewContent)
{
	var alertView = UIAlertView()

	alertView.title = content.title
	alertView.message = content.msg
	alertView.delegate = sender
	alertView.addButtonWithTitle(content.btn)
	alertView.show()
}

/*
** Display networking activity
*/
func networkActivity(state: Bool) {
	UIApplication.sharedApplication().networkActivityIndicatorVisible = state
}
