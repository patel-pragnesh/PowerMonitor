//
//  Socket.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 07/02/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import Foundation

class Socket: NSStream, NSStreamDelegate {
	var _connected: Bool = false
	var _host: String!
	var _port: Int!

	var _inputStream: NSInputStream?
	var _outputStream: NSOutputStream?
	var _ISOK: Bool = false
	var _OSOK: Bool = false

	/*
	** Try to connect to the given host:port
	** Async operation, success event will be caugth by stream
	*/
	func connect(host: String, port: Int) {
		//clear the previous connection if existing
		disconnect()
		_host = host
		_port = port

		//pairing NSstreams with remote connection
		NSStream.getStreamsToHostWithName(_host!, port: _port!, inputStream: &_inputStream, outputStream: &_outputStream)

		if (_inputStream != nil && _outputStream != nil) {
			//set the delegate to self
			_inputStream!.delegate = self
			_outputStream!.delegate = self
			// Schedule
			_inputStream!.scheduleInRunLoop(.mainRunLoop(), forMode: NSDefaultRunLoopMode)
			_outputStream!.scheduleInRunLoop(.mainRunLoop(), forMode: NSDefaultRunLoopMode)
			println("Streams open()")
			//open streams
			_inputStream!.open()
			_outputStream!.open()
		}
	}

	/*
  ** Delegate event handler
	*/
	func stream(aStream: NSStream, handleEvent eventCode: NSStreamEvent) {
		if aStream === _inputStream {
			switch eventCode {
			case NSStreamEvent.ErrorOccurred:
				println("input: ErrorOccurred: \(aStream.streamError?.description)")
			case NSStreamEvent.OpenCompleted:
				_ISOK = true
				//println("input: OpenCompleted")
			case NSStreamEvent.HasBytesAvailable:
				println("")//"input: HasBytesAvailable"
			default:
				break
			}
		}
		else if aStream === _outputStream {
			switch eventCode {
			case NSStreamEvent.ErrorOccurred:
				println("output: ErrorOccurred: \(aStream.streamError?.description)")
			case NSStreamEvent.OpenCompleted:
				_OSOK = true
				//println("output: OpenCompleted")
			case NSStreamEvent.HasSpaceAvailable:
				println("")//"output: HasSpaceAvailable"
			default:
				break
			}
		}
		_connected = _OSOK && _ISOK
		if (_connected) {
			println(">>> CONNECT OK")
		}
	}

	// ------------------------------------------------------------------------ //

	/*
	** End the current socket connection if existing
	*/
	func disconnect() {
		if _connected {
			_inputStream?.close()
			_outputStream?.close()
			_ISOK = false
			_OSOK = false
			_connected = false
		}
	}

	/*
	** Read maxReadSize bytes on the inputStream
	** Return the Byte array of read bytes
	** Error handling
	*/
	func read(maxReadSize: Int) -> [UInt8] {
		var readBuffer = [UInt8]()

		readBuffer = [UInt8](count: maxReadSize, repeatedValue: 0)
		let readSize = _inputStream!.read(&readBuffer, maxLength: maxReadSize)
		if (readSize == -1) {
			println("[ERR]SocketWrite() : Err")
		}
		else {
			if (readSize < maxReadSize) {
				readBuffer.removeRange(readSize...maxReadSize - 1)
			}
		}
		//println("Read :[\(readBuffer.description)]")
		return readBuffer
	}

	/*
	**
	**
	*/
	func writeData(data: NSData) -> Bool {
		var dataBytes = [UInt8]()
		var bytesToWrite :Int = data.length
		var totalBytesWritten :Int = 0

		if (_outputStream!.hasSpaceAvailable) {
			dataBytes = [UInt8](count: data.length, repeatedValue: 0)
			data.getBytes(&dataBytes, length: data.length)
			while (totalBytesWritten != bytesToWrite) {
				let bytesWritten = _outputStream!.write(dataBytes, maxLength: dataBytes.count)

				//println("Write :[\(dataBytes.description)]")
				if (bytesWritten == -1) {
					println("[ERR]SocketWrite() : Err")
					return false
				}
				totalBytesWritten += bytesWritten
				dataBytes.removeRange(0...bytesWritten - 1)
			}
			return true
		}
		return false
	}

}