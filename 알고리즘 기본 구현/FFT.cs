using System.Numerics;

namespace MyApp {
    static class FFT {
        private static int CountTrailingZeros(int n) {
            for (int i = 0; i < 31; ++i) {
                if ((n & (1<<i)) > 0) {
                    return i;
                }
            }
            throw new ArgumentException();
        }

        private static int ReverseBits(int n, int k) {
            int r, i;
            for (r = 0, i = 0; i < k; ++i) {
                r |= ((n >> i) & 1) << (k - i - 1);
            }
            return r;
        }

        private static void _FFT(IList<Complex> a, bool isReversed = false) {
            int n = a.Count;
            int k = CountTrailingZeros(n);

            for (int i = 0; i < n; i++) {
                int j = ReverseBits(i, k);
                if (i < j) {
                    var t = a[i];
                    a[i] = a[j];
                    a[j] = t;
                }
            }
            for (int s = 2; s <= n; s *= 2) {
                List<Complex> w = new List<Complex>(s / 2);
                for (int i = 0; i < s / 2; i++) {
                    double t = 2 * Math.PI * i / s * (isReversed ? -1 : 1);
                    w.Add(new Complex(Math.Cos(t), Math.Sin(t)));
                }
                for (int i = 0; i < n; i += s) {
                    for (int j = 0; j < s / 2; j++) {
                        Complex tmp = a[i + j + s / 2] * w[j];
                        a[i + j + s / 2] = a[i + j] - tmp;
                        a[i + j] += tmp;
                    }
                }
            }
            if (isReversed) {
                for (int i = 0; i < n; i++) {
                    a[i] /= n;
                }
            }
        }

        public static List<Complex> GetConvolution(IList<Complex> a, IList<Complex> b) {
            var aCopy = new List<Complex>(a);
            var bCopy = new List<Complex>(b);
            int n = 1;
            while (n < a.Count + b.Count) {
                n *= 2;
            }

            aCopy.Capacity = n;
            while (aCopy.Count < n) {
                aCopy.Add(new Complex(0, 0));
            }
            _FFT(aCopy);

            bCopy.Capacity = n;
            while (bCopy.Count < n) {
                bCopy.Add(new Complex(0, 0));
            }
            _FFT(bCopy);

            List<Complex> result = new List<Complex>(n);
            for (int i = 0; i < n; ++i) {
                result.Add(aCopy[i] * bCopy[i]);
            }
            _FFT(result, true);
            return result;
        }
    }
}