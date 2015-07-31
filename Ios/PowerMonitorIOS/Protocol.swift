//
//  PacketProtocol.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 08/02/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

let D_HeaderSize: Int						= 4
let D_ReadSize: Int							= 512
let D_ReadPacketSizeError: Int	= 0

class Protocol {
	var _socket = Socket()

	// Connect sockets streams to host:port
	func connect(host: String, port: Int) {
		_socket.connect(host, port: port)
	}

	// Close the current socket streams
	func disconnect() {
		_socket.disconnect()
	}

	func isConnected() -> Bool {
		return (_socket._connected)
	}
	/* ------------------------------------------------------------------------ */

	/*
	** Read an incoming packet
	** Return a NSData containing the paquet bytes
	*/
	func readPacket() -> NSData {
		var bytesRead :Int = 0
		var packetSize :Int = 0
		var tmpBuffer = [UInt8]()
		var tmpDataBuffer = [UInt8]()
		var packetData :NSData!
		var errorFlag :Bool = false

		packetSize = readPacketSize()
		//verify if packet header has been read properly
		if (packetSize != D_ReadPacketSizeError) {
			//read packet content
			while (bytesRead < packetSize) {
				tmpBuffer = _socket.read(D_ReadSize)
				if tmpBuffer.count > 0 {
					tmpDataBuffer += tmpBuffer
					bytesRead += tmpBuffer.count
				}
			}
		}
		if (!errorFlag) {
			packetData = NSData(bytes: &tmpDataBuffer, length: packetSize)
		}
		return packetData
	}

	/*
	** Send a packet
	** return the result of the operation (OK/NOK)
	*/
	func writePaquet(paquetJSON :JSON) -> Bool {
		var data = NSMutableData()
		var paquetSize: UInt32
		var paquetBytes: Int = 4

		paquetSize = CFSwapInt32HostToBig(UInt32(paquetJSON.rawData()!.length))
		data.appendBytes(&paquetSize, length: 4)
		data.appendData(paquetJSON.rawData()!)
		if (_socket.writeData(data)) {
			return true
		}
		return false
	}

	/*
	** USEDBY readPacket()
	** Read the header of an incoming packet
	** The header represent the length of the data contained by the packet
	*/
	private func readPacketSize() -> Int {
		var headerBuffer = [UInt8]()
		var packetLength: Int = 0

		//read the 4 bytes of header
		headerBuffer = _socket.read(D_HeaderSize)
		//check integrity
		if (headerBuffer.count == D_HeaderSize) {
			var tmp = UnsafePointer<UInt32>(headerBuffer).memory
			//convert big endian to host endianness
			tmp = CFSwapInt32BigToHost(tmp)
			//convert to the corresponding Int value
			packetLength = Int(tmp)
		}
		else {
			println("[ERR]ReadPacketSize() : wrong header size")
			packetLength = D_ReadPacketSizeError
		}
		return packetLength
	}
}