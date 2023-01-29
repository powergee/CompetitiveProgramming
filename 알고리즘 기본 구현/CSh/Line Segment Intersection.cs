using System;
using System.Linq;

namespace LineSegmentIntersection {
    public record Point(long X, long Y) {
        public static bool operator<=(Point p1, Point p2) {
            if (p1.X != p2.X) {
                return p1.X <= p2.X;
            }
            return p1.Y <= p2.Y;
        }

        public static bool operator>=(Point p1, Point p2) {
            if (p1.X != p2.X) {
                return p1.X >= p2.X;
            }
            return p1.Y >= p2.Y;
        }

        public static (Point, Point) SortPair(Point p1, Point p2) {
            return p1 <= p2 ? (p1, p2) : (p2, p1);
        }
    }

    public record Line(Point P1, Point P2) {
        private int CCW(Point p1, Point p2, Point p3) {
            long op = p1.X*p2.Y + p2.X*p3.Y + p3.X*p1.Y
                    - p1.Y*p2.X - p2.Y*p3.X - p3.Y*p1.X;
            if (op < 0) {
                return 1;
            } else if (op == 0) {
                return 0;
            } else {
                return -1;
            }
        }

        public bool IsCrossed(Line other) {
            int ab = CCW(P1, P2, other.P1) * CCW(P1, P2, other.P2);
            int cd = CCW(other.P1, other.P2, P1) * CCW(other.P1, other.P2, P2);

            if (ab == 0 && cd == 0) {
                var (a, b) = Point.SortPair(P1, P2);
                var (c, d) = Point.SortPair(other.P1, other.P2);
                return c <= b && a <= d;
            }
            return ab <= 0 && cd <= 0;
        }
    }
}
