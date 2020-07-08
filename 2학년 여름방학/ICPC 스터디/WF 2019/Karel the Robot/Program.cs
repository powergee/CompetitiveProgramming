using System;
using System.IO;
using System.Collections.Generic;

namespace Karel_the_Robot
{
    class MainClass
    {
        static void Main(string[] args)
        {
            StreamReader reader = new StreamReader(Console.OpenStandardInput());
            StreamWriter writer = new StreamWriter(Console.OpenStandardOutput());

            string[] rcde = reader.ReadLine().Split(' ');
            int r = int.Parse(rcde[0]);
            int c = int.Parse(rcde[1]);
            int d = int.Parse(rcde[2]);
            int e = int.Parse(rcde[3]);

            string[] rows = new string[r];
            for (int i = 0; i < r; ++i)
                rows[i] = reader.ReadLine();
            Map map = new Map(r, c, rows);

            for (int i = 0; i < d; ++i)
                new Procedure(reader.ReadLine());
            
            for (int i = 0; i < e; ++i)
            {
                Console.WriteLine($"Executing {i}...");
                string[] init = reader.ReadLine().Split(' ');
                map.Initialize(int.Parse(init[0]) - 1, int.Parse(init[1]) - 1, init[2][0]);

                string code = reader.ReadLine();
                int start = 0;
                Program prog = new Program(code, ref start);
                try
                {
                    prog.Execute(map);
                    writer.WriteLine(map.State.ToString());
                    //Console.WriteLine(map.State.ToString());
                }
                catch (NeverTerminatingException)
                {
                    writer.WriteLine("inf");
                    //Console.WriteLine("inf");
                }
            }

            reader.Close();
            writer.Close();
        }
    }

    enum Direction : short { East = (short)'e', West = (short)'w', South = (short)'s', North = (short)'n' }

    struct Pair
    {
        public int Item1, Item2;

        public Pair(int i1, int i2)
        {
            Item1 = i1;
            Item2 = i2;
        }
    }

    struct RobotState
    {
        public int Row { get; set; }
        public int Col { get; set; }
        public Pair Position
        {
            get => new Pair(Row, Col);

            set
            {
                Row = value.Item1;
                Col = value.Item2;
            }
        }
        public Direction Facing { get; set; }

        public override int GetHashCode()
        {
            return (Row << 24) + (Col << 16) + ((short)Facing);
        }

        public override string ToString()
        {
            return $"{Row + 1} {Col + 1} {(char)((short)Facing)}";
        }
    }

    class Map
    {
        private bool[,] isFree;
        private RobotState state;

        public bool this[int r, int c] => isFree[r, c];
        public int Width { get; }
        public int Height { get; }
        
        public RobotState State 
        {
            get => state;
            set => state = value;
        }

        private Pair MovedPosition
        {
            get
            {
                Pair moved = State.Position;
                switch (State.Facing)
                {
                case Direction.East:
                    ++moved.Item2;
                    break;
                case Direction.West:
                    --moved.Item2;
                    break;
                case Direction.South:
                    ++moved.Item1;
                    break;
                case Direction.North:
                    --moved.Item1;
                    break;
                }

                return moved;
            }
        }

        public bool IsAbleToMove
        {
            get
            {
                Pair moved = MovedPosition;
                
                int row = moved.Item1;
                int col = moved.Item2;

                return 0 <= row && row < Height && 0 <= col && col < Width && isFree[row, col];
            }
        }

        public Map(int rCount, int cCount, string[] rows)
        {
            Width = cCount;
            Height = rCount;

            isFree = new bool[rCount, cCount];
            for (int row = 0; row < rCount; ++row)
                for (int col = 0; col < cCount; ++col)
                    isFree[row, col] = (rows[row][col] == '.' ? true : false);
        }

        public void Initialize(int robotRow, int robotCol, char dir)
        {
            state.Position = new Pair(robotRow, robotCol);
            state.Facing = (Direction)dir;
        }

        public void MoveRobot()
        {
            if (!IsAbleToMove)
                return;
            state.Position = MovedPosition;
        }

        public void TurnLeft()
        {
            switch (State.Facing)
            {
            case Direction.East:
                state.Facing = Direction.North;
                break;
            case Direction.West:
                state.Facing = Direction.South;
                break;
            case Direction.South:
                state.Facing = Direction.East;
                break;
            case Direction.North:
                state.Facing = Direction.West;
                break;
            }
        }
    }

    class Program
    {
        private List<Command> commands;
        private HashSet<int>[] stateHistory;

        public Program(string code, ref int start)
        {
            commands = new List<Command>();
            while (start < code.Length && Command.IsCommand(code[start]))
                commands.Add(new Command(code, ref start));

            stateHistory = new HashSet<int>[commands.Count];
            for (int i = 0; i < commands.Count; ++i)
                stateHistory[i] = new HashSet<int>();
        }

        public void Execute(Map map)
        {
            int pc = 0;
            
            while (pc < commands.Count)
            {
                int stateHash = map.State.GetHashCode();
                if (stateHistory[pc].Contains(stateHash))
                    throw new NeverTerminatingException();
                
                stateHistory[pc].Add(stateHash);
                commands[pc].Execute(map);
                stateHistory[pc].Remove(stateHash);
                
                ++pc;
            }
        }
    }

    class NeverTerminatingException : Exception { }

    class Command
    {
        private char comChar;
        private Condition condition;
        private Program[] childProgs;
        private char childProc = '\0';
        private Dictionary<int, RobotState> execHistory = new Dictionary<int, RobotState>();

        public Command(string code, ref int start)
        {
            if (!IsCommand(code[start]))
                throw new InvalidOperationException();
            
            comChar = code[start++];
            if ('A' <= comChar && comChar <= 'Z')
            {
                childProc = comChar;
            }
            else
            {
                switch (comChar)
                {
                case 'm':
                case 'l':
                    break;
                
                case 'i':
                    childProgs = new Program[2];

                    condition = new Condition(code, ref start);
                    ++start;
                    childProgs[0] = new Program(code, ref start);
                    start += 2;
                    childProgs[1] = new Program(code, ref start);
                    ++start;
                    break;

                case 'u':
                    childProgs = new Program[1];
                    
                    condition = new Condition(code, ref start);
                    ++start;
                    childProgs[0] = new Program(code, ref start);
                    ++start;
                    break;
                }
            }
        }

        public void Execute(Map map)
        {
            if (execHistory.ContainsKey(map.State.GetHashCode()))
                map.State = execHistory[map.State.GetHashCode()];

            int prevState = map.State.GetHashCode();
            if (childProc != '\0')
                Procedure.FindProcByID(childProc).Execute(map);
            else
            {
                switch (comChar)
                {
                case 'm':
                    map.MoveRobot();
                    break;

                case 'l':
                    map.TurnLeft();
                    break;
                
                case 'i':
                    if (condition.IsSatisfied(map))
                        childProgs[0].Execute(map);
                    else childProgs[1].Execute(map);
                    break;

                case 'u':
                    HashSet<int> prevStates = new HashSet<int>();
                    prevStates.Add(map.State.GetHashCode());
                    while (!condition.IsSatisfied(map))
                    {
                        childProgs[0].Execute(map);
                        if (prevStates.Contains(map.State.GetHashCode()))
                            throw new NeverTerminatingException();
                        prevStates.Add(map.State.GetHashCode());
                    }
                    break;
                }
            }

            if (!execHistory.ContainsKey(prevState))
                execHistory.Add(prevState, map.State);
        }

        public static bool IsCommand(char ch)
        {
            return ch == 'm' || ch == 'l' || ch == 'i' || ch == 'u' || ('A' <= ch && ch <= 'Z');
        }
    }

    class Condition
    {
        private char condChar;

        public Condition(string code, ref int start)
        {
            condChar = code[start++];
        }

        public bool IsSatisfied(Map map)
        {
            switch (condChar)
            {
            case 'b':
                return !map.IsAbleToMove;
            case 'n':
                return map.State.Facing == Direction.North;
            case 's':
                return map.State.Facing == Direction.South;
            case 'e':
                return map.State.Facing == Direction.East;
            case 'w':
                return map.State.Facing == Direction.West;
            }

            return false;
        }
    }

    class Procedure
    {
        private char id;
        private Program body;
        private Dictionary<int, RobotState> execHistory = new Dictionary<int, RobotState>();

        public Procedure(string defCode)
        {
            id = defCode[0];
            int start = 2;
            body = new Program(defCode, ref start);

            procDict.Add(id, this);
        }

        public void Execute(Map map)
        {
            if (execHistory.ContainsKey(map.State.GetHashCode()))
                map.State = execHistory[map.State.GetHashCode()];

            int prevState = map.State.GetHashCode();
            body.Execute(map);

            if (!execHistory.ContainsKey(prevState))
                execHistory.Add(prevState, map.State);
        }

        private static Dictionary<char, Procedure> procDict = new Dictionary<char, Procedure>();

        public static Procedure FindProcByID(char id)
        {
            if (procDict.ContainsKey(id))
                return procDict[id];
            return null;
        }
    }
}
