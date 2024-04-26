public interface Calculator {
    class CalculatorImpl extends java.rmi.server.UnicastRemoteObject
            implements Calculator {
        // Реализации должны иметь явный конструктор для того, чтобы объявить
// исключительную ситуацию RemoteException
        public CalculatorImpl()
                throws java.rmi.RemoteException {
            super();
        }
        public long add(long a, long b) throws java.rmi.RemoteException {
            return a + b;
        }
        public long sub(long a, long b) throws java.rmi.RemoteException {
            return a - b;
        }
        public long mul(long a, long b) throws java.rmi.RemoteException {
            return a * b;
        }
        public long div(long a, long b) throws java.rmi.RemoteException {
            return a / b;
        }
    }

}
