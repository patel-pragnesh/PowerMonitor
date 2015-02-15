using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Networking;
using Windows.Networking.Sockets;
using Windows.Storage.Streams;

namespace Powermonitor.Common
{
    public class Socket
    {
        private readonly StreamSocket _clientSocket;
        private bool _connected;
        private DataReader _dataReader;
        public ObservableCollection<String> Received { get; private set; }

        public Socket()
        {
            _clientSocket = new StreamSocket();
            Received = new ObservableCollection<string>();
        }

        public async Task<bool> Connect()
        {
            if (_connected) return false;
            var hostname = new HostName("192.168.1.11");
            await _clientSocket.ConnectAsync(hostname, "8080");
            _connected = true;
            _dataReader = new DataReader(_clientSocket.InputStream)
            {
                InputStreamOptions = InputStreamOptions.Partial
            };
            ReadData();
            return true;

        }

        async private void ReadData()
        {
            if (!_connected || _clientSocket == null) return;
            uint s = await _dataReader.LoadAsync(4);
            byte[] sizeBuff = new byte[4];
            _dataReader.ReadBytes(sizeBuff);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(sizeBuff);
            uint size = BitConverter.ToUInt32(sizeBuff, 0);
            uint totalRead = 0;
            string data = "";
            while (totalRead < size)
            {
                uint actual = await _dataReader.LoadAsync(size - totalRead);
                data += _dataReader.ReadString(actual);
                totalRead += actual;
            }
            System.Diagnostics.Debug.WriteLine("Received : " + data);
            Received.Add(data);
            ReadData();
        }

        async public void SendRawMessage(string message)
        {
            var writer = new DataWriter(_clientSocket.OutputStream);
            byte[] header = BitConverter.GetBytes(message.Length);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(header);
            writer.WriteBytes(header);
            writer.WriteString(message);
            await writer.StoreAsync();
            await writer.FlushAsync();
            System.Diagnostics.Debug.WriteLine("Sent : header = " + BitConverter.ToString(header) + " | body = " + message);
            writer.DetachStream();
            //_clientSocket.Dispose();
            //_connected = false;
        }
    }
}
