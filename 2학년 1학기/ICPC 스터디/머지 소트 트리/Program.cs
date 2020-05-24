using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;

namespace 머지_소트_트리
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader input = new StreamReader(Console.OpenStandardInput());
            StringBuilder output = new StringBuilder();

            int n = int.Parse(input.ReadLine());
            List<int> arr = new List<int>();
            foreach (string val in input.ReadLine().Split(' '))
                arr.Add(int.Parse(val));

            MergeSortTree<int> tree = new MergeSortTree<int>(arr.ToArray());
            int qCount = int.Parse(input.ReadLine());
            int prev = 0;
            for (int i = 0; i < qCount; ++i)
            {
                string[] queryStr = input.ReadLine().Split(' ');
                int[] query = new int[3];
                query[0] = int.Parse(queryStr[0]) ^ prev;
                query[1] = int.Parse(queryStr[1]) ^ prev;
                query[2] = int.Parse(queryStr[2]) ^ prev;

                prev = tree.Query(query[0] - 1, query[1] - 1, query[2]);
                output.AppendLine(prev.ToString());
            }

            Console.WriteLine(output.ToString());
        }
    }

    class Node<T> : List<T> where T : IComparable<T>
    {
        public int LeftIndex { get; }
        public int RightIndex { get; }
        public Node<T> LeftNode { get; set; }
        public Node<T> RightNode { get; set; }

        public Node(int left, int right)
        {
            LeftIndex = left;
            RightIndex = right;
        }

        public int Query(int left, int right, T val)
        {
            if (right < LeftIndex || RightIndex < left)
                return 0;
            else if (left <= LeftIndex && RightIndex <= right)
                return CountElements(val);
            else
                return LeftNode.Query(left, right, val) + RightNode.Query(left, right, val);
        }

        private int CountElements(T pivot)
        {
            int index = BinarySearch(pivot);
            if (index < 0)
                return Count - ~index;
            else return Count - index - 1;
        }
    }

    class MergeSortTree<T> where T : IComparable<T>
    {
        public Node<T> Top { get; }

        public MergeSortTree(T[] arr)
        {
            Top = MergeSort(arr, 0, (int)arr.Length - 1);
        }

        private Node<T> MergeSort(T[] arr, int left, int right)
        {
            if (left == right)
            {
                Node<T> leaf = new Node<T>(left, right);
                leaf.Add(arr[left]);
                return leaf;
            }

            int length = right - left + 1;
            int med = (left + right) / 2;
            Node<T> leftNode = MergeSort(arr, left, med);
            Node<T> rightNode = MergeSort(arr, med + 1, right);
            Node<T> currNode = new Node<T>(left, right)
            {
                LeftNode = leftNode,
                RightNode = rightNode
            };

            int i = 0, j = 0;
            while (currNode.Count < length)
            {
                if (leftNode[i].CompareTo(rightNode[j]) < 0)
                    currNode.Add(leftNode[i++]);
                else
                    currNode.Add(rightNode[j++]);

                if (i >= leftNode.Count)
                    while (j < rightNode.Count)
                        currNode.Add(rightNode[j++]);

                else if (j >= rightNode.Count)
                    while (i < leftNode.Count)
                        currNode.Add(leftNode[i++]);
            }

            return currNode;
        }

        public int Query(int left, int right, T val)
        {
            return Top.Query(left, right, val);
        }
    }
}