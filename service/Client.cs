﻿using Microsoft.AspNetCore.Authentication.OAuth.Claims;
using System.Net;
using System.Net.Sockets;
using System.Text;
using Serilog;
using Microsoft.AspNetCore.Http;

namespace service
{
    public class Client
    {
        private IPEndPoint _ipEndPoint;
        private TcpClient _tcpClient;
        private byte[] _buffer;
        private int _bufferSize;

        public Client(byte[] buffer, int bufferSize)
        {
            _ipEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8888);
            _tcpClient = new TcpClient();
            _buffer = buffer;
            _bufferSize = bufferSize;
        }

        public void SendMessageToServer()
        {
            _tcpClient.Connect(_ipEndPoint);
            NetworkStream stream = _tcpClient.GetStream();
            stream.BeginWrite(_buffer, 0, _bufferSize, null, null);
        }

    }
}