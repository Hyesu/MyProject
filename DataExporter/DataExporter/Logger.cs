using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataExporter
{
    public delegate void LoggerImpl(string log);

    class Logger
    {
        private LoggerImpl _logger;

        public void AddLogger(LoggerImpl logger)
        {
            if(_logger == null)
            {
                _logger = logger;
            }
            else
            {
                _logger += logger;
            }
        }

        public void Write(string log)
        {
            _logger(log);
        }
    }
}
