using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Networking.Sockets;
using System.Threading;
using Windows.Networking;
using Windows.Storage.Streams;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Collections;

namespace Powermonitor.Common
{
    public class Sockets
    {
        private readonly StreamSocket _clientSocket;
        private bool _connected;
        private DataReader _dataReader;
        private ObservableCollection<String> _toSend;
        private ObservableCollection<String> _received;

        public Sockets()
        {
            _clientSocket = new StreamSocket();
            this.Connect();
            _toSend = new ObservableCollection<string>();
            _toSend.CollectionChanged += sendMsgs;
            _received = new ObservableCollection<string>();
        }
        
       private async Task<bool> Connect()
        {
            if (_connected) return false;
            var hostname = new HostName("127.0.0.1");
            await _clientSocket.ConnectAsync(hostname, "4242");
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
            uint s = await _dataReader.LoadAsync(2048);
            string data = _dataReader.ReadString(s);
            _received.Add(data);
            ReadData();
        }

        async public void SendRawMessage(string message)
        {
            var writer = new DataWriter(_clientSocket.OutputStream);
            writer.WriteString(message + "\r\n");
            await writer.StoreAsync();
            await writer.FlushAsync();
            writer.DetachStream();
           //_clientSocket.Dispose();
            //_connected = false;
        }

        private void sendMsgs(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (_toSend.Count > 0)
            {
                String msg = _toSend.First();
                SendRawMessage(msg);
                _toSend.Remove(msg);
            }
        }

        public void addMsg(string msg)
        {
            _toSend.Add(msg);
        }
    }
}
