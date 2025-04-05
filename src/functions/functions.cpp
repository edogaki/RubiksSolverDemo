#include <emscripten/bind.h>
#include <emscripten.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <sstream>

std::vector<std::string> move_names = {"U", "U2", "U'", "D", "D2", "D'", "L", "L2", "L'", "R", "R2", "R'", "F", "F2", "F'", "B", "B2", "B'"};
std::unordered_map<std::string, std::string> move_convert =
	{
		{"U", "U"},
		{"U2", "U2"},
		{"U2'", "U2"},
		{"U'", "U'"},
		{"D", "D"},
		{"D2", "D2"},
		{"D2'", "D2"},
		{"D'", "D'"},
		{"L", "L"},
		{"L2", "L2"},
		{"L2'", "L2"},
		{"L'", "L'"},
		{"R", "R"},
		{"R2", "R2"},
		{"R2'", "R2"},
		{"R'", "R'"},
		{"F", "F"},
		{"F2", "F2"},
		{"F2'", "F2"},
		{"F'", "F'"},
		{"B", "B"},
		{"B2", "B2"},
		{"B2'", "B2"},
		{"B'", "B'"},
		{"u", "y D"},
		{"u2", "y2 D2"},
		{"u2'", "y2 D2"},
		{"u'", "y' D'"},
		{"Uw", "y D"},
		{"Uw2", "y2 D2"},
		{"Uw2'", "y2 D2"},
		{"Uw'", "y' D'"},
		{"d", "y' U"},
		{"d2", "y2 U2"},
		{"d2'", "y2 U2"},
		{"d'", "y U'"},
		{"Dw", "y' U"},
		{"Dw2", "y2 U2"},
		{"Dw2'", "y2 U2"},
		{"Dw'", "y U'"},
		{"l", "x' R"},
		{"l2", "x2 R2"},
		{"l2'", "x2 R2"},
		{"l'", "x R'"},
		{"Lw", "x' R"},
		{"Lw2", "x2 R2"},
		{"Lw2'", "x2 R2"},
		{"Lw'", "x R'"},
		{"r", "x L"},
		{"r2", "x2 L2"},
		{"r2'", "x2 L2"},
		{"r'", "x' L'"},
		{"Rw", "x L"},
		{"Rw2", "x2 L2"},
		{"Rw2'", "x2 L2"},
		{"Rw'", "x' L'"},
		{"f", "z B"},
		{"f2", "z2 B2"},
		{"f2'", "z2 B2"},
		{"f'", "z' B'"},
		{"Fw", "z B"},
		{"Fw2", "z2 B2"},
		{"Fw2'", "z2 B2"},
		{"Fw'", "z' B'"},
		{"b", "z' F"},
		{"b2", "z2 F2"},
		{"b2'", "z2 F2"},
		{"b'", "z F'"},
		{"Bw", "z' F"},
		{"Bw2", "z2 F2"},
		{"Bw2'", "z2 F2"},
		{"Bw'", "z F'"},
		{"M", "x' L' R"},
		{"M2", "x2 L2 R2"},
		{"M2'", "x2 L2 R2"},
		{"M'", "x L R'"},
		{"E", "y' U D'"},
		{"E2", "y2 U2 D2"},
		{"E2'", "y2 U2 D2"},
		{"E'", "y U' D"},
		{"S", "z F' B"},
		{"S2", "z2 F2 B2"},
		{"S2'", "z2 F2 B2"},
		{"S'", "z' F B'"}};

std::unordered_map<std::string, std::string> move_mirror = {
	{"U", "U'"},
	{"U2", "U2'"},
	{"U2'", "U2"},
	{"U'", "U"},
	{"D", "D'"},
	{"D2", "D2'"},
	{"D2'", "D2"},
	{"D'", "D"},
	{"L", "R'"},
	{"L2", "R2'"},
	{"L2'", "R2"},
	{"L'", "R"},
	{"R", "L'"},
	{"R2", "L2'"},
	{"R2'", "L2"},
	{"R'", "L"},
	{"F", "F'"},
	{"F2", "F2'"},
	{"F2'", "F2"},
	{"F'", "F"},
	{"B", "B'"},
	{"B2", "B2'"},
	{"B2'", "B2"},
	{"B'", "B"},
	{"u", "u'"},
	{"u2", "u2'"},
	{"u2'", "u2"},
	{"u'", "u"},
	{"Uw", "Uw'"},
	{"Uw2", "Uw2'"},
	{"Uw2'", "Uw2"},
	{"Uw'", "Uw"},
	{"d", "d'"},
	{"d2", "d2'"},
	{"d2'", "d2"},
	{"d'", "d"},
	{"Dw", "Dw'"},
	{"Dw2", "Dw2'"},
	{"Dw2'", "Dw2"},
	{"Dw'", "Dw"},
	{"l", "r'"},
	{"l2", "r2'"},
	{"l2'", "r2"},
	{"l'", "r"},
	{"Lw", "Rw'"},
	{"Lw2", "Rw2'"},
	{"Lw2'", "Rw2"},
	{"Lw'", "Rw"},
	{"r", "l'"},
	{"r2", "l2'"},
	{"r2'", "l2"},
	{"r'", "l"},
	{"Rw", "Lw'"},
	{"Rw2", "Lw2'"},
	{"Rw2'", "Lw2"},
	{"Rw'", "Lw"},
	{"f", "f'"},
	{"f2", "f2'"},
	{"f2'", "f2"},
	{"f'", "f"},
	{"Fw", "Fw'"},
	{"Fw2", "Fw2'"},
	{"Fw2'", "Fw2"},
	{"Fw'", "Fw"},
	{"b", "b'"},
	{"b2", "b2'"},
	{"b2'", "b2"},
	{"b'", "b"},
	{"Bw", "Bw'"},
	{"Bw2", "Bw2'"},
	{"Bw2'", "Bw2"},
	{"Bw'", "Bw"},
	{"M", "M"},
	{"M2", "M2"},
	{"M2'", "M2'"},
	{"M'", "M'"},
	{"E", "E'"},
	{"E2", "E2'"},
	{"E2'", "E2"},
	{"E'", "E"},
	{"S", "S'"},
	{"S2", "S2'"},
	{"S2'", "S2"},
	{"S'", "S"}};

std::unordered_map<std::string, std::string> move_reverse = {
	{"U", "U'"},
	{"U2", "U2'"},
	{"U2'", "U2"},
	{"U'", "U"},
	{"D", "D'"},
	{"D2", "D2'"},
	{"D2'", "D2"},
	{"D'", "D"},
	{"L", "L'"},
	{"L2", "L2'"},
	{"L2'", "L2"},
	{"L'", "L"},
	{"R", "R'"},
	{"R2", "R2'"},
	{"R2'", "R2"},
	{"R'", "R"},
	{"F", "F'"},
	{"F2", "F2'"},
	{"F2'", "F2"},
	{"F'", "F"},
	{"B", "B'"},
	{"B2", "B2'"},
	{"B2'", "B2"},
	{"B'", "B"},
	{"u", "u'"},
	{"u2", "u2'"},
	{"u2'", "u2"},
	{"u'", "u"},
	{"Uw", "Uw'"},
	{"Uw2", "Uw2'"},
	{"Uw2'", "Uw2"},
	{"Uw'", "Uw"},
	{"d", "d'"},
	{"d2", "d2'"},
	{"d2'", "d2"},
	{"d'", "d"},
	{"Dw", "Dw'"},
	{"Dw2", "Dw2'"},
	{"Dw2'", "Dw2"},
	{"Dw'", "Dw"},
	{"l", "l'"},
	{"l2", "l2'"},
	{"l2'", "l2"},
	{"l'", "l"},
	{"Lw", "Lw'"},
	{"Lw2", "Lw2'"},
	{"Lw2'", "Lw2"},
	{"Lw'", "Lw"},
	{"r", "r'"},
	{"r2", "r2'"},
	{"r2'", "r2"},
	{"r'", "r"},
	{"Rw", "Rw'"},
	{"Rw2", "Rw2'"},
	{"Rw2'", "Rw2"},
	{"Rw'", "Rw"},
	{"f", "f'"},
	{"f2", "f2'"},
	{"f2'", "f2"},
	{"f'", "f"},
	{"Fw", "Fw'"},
	{"Fw2", "Fw2'"},
	{"Fw2'", "Fw2"},
	{"Fw'", "Fw"},
	{"b", "b'"},
	{"b2", "b2'"},
	{"b2'", "b2"},
	{"b'", "b"},
	{"Bw", "Bw'"},
	{"Bw2", "Bw2'"},
	{"Bw2'", "Bw2"},
	{"Bw'", "Bw"},
	{"M", "M'"},
	{"M2", "M2'"},
	{"M2'", "M2"},
	{"M'", "M"},
	{"E", "E'"},
	{"E2", "E2'"},
	{"E2'", "E2"},
	{"E'", "E"},
	{"S", "S'"},
	{"S2", "S2'"},
	{"S2'", "S2"},
	{"S'", "S"}};

std::unordered_map<std::string, std::string> rotation_mirror = {
	{"z", "z'"},
	{"z2", "z2'"},
	{"z2'", "z2"},
	{"z'", "z"},
	{"y", "y'"},
	{"y2", "y2'"},
	{"y2'", "y2"},
	{"y'", "y"},
	{"x", "x"},
	{"x2", "x2"},
	{"x2'", "x2'"},
	{"x'", "x'"}};

std::unordered_map<std::string, std::string> rotation_reverse = {
	{"z", "z'"},
	{"z2", "z2'"},
	{"z2'", "z2"},
	{"z'", "z"},
	{"y", "y'"},
	{"y2", "y2'"},
	{"y2'", "y2"},
	{"y'", "y"},
	{"x", "x'"},
	{"x2", "x2'"},
	{"x2'", "x2"},
	{"x'", "x"}};

std::string AlgToString(std::vector<int> &alg)
{
	std::string result = "";
	for (int i : alg)
	{
		result += move_names[i] + " ";
	}
	return result;
}

std::vector<int> StringToAlg(std::string &str)
{
	std::vector<int> alg;
	std::istringstream iss(str);
	std::string name;
	while (iss >> name)
	{
		if (!name.empty())
		{
			auto it = std::find(move_names.begin(), move_names.end(), name);
			if (it != move_names.end())
			{
				alg.emplace_back(std::distance(move_names.begin(), it));
			}
		}
	}
	return alg;
}

std::string MirrorScramble(std::string str)
{
	std::string result = "";
	std::istringstream iss(str);
	std::string name;
	while (iss >> name)
	{
		if (move_mirror.count(name) > 0)
		{
			result += move_mirror[name] + " ";
		}
		else if (rotation_mirror.count(name) > 0)
		{
			result += rotation_mirror[name] + " ";
		}
	}
	return result;
}

std::string ReverseScramble(std::string str)
{
	std::reverse(str.begin(), str.end());
	std::string result = "";
	std::istringstream iss(str);
	std::string name;
	while (iss >> name)
	{
		std::reverse(name.begin(), name.end());
		if (move_reverse.count(name) > 0)
		{
			result += move_reverse[name] + " ";
		}
		else if (rotation_reverse.count(name) > 0)
		{
			result += rotation_reverse[name] + " ";
		}
	}
	return result;
}

std::vector<int> AlgConvertRotation(std::vector<int> &alg, std::string &rotation)
{
	if (rotation.empty())
	{
		return alg;
	}
	std::vector<int> face_list_0 = {0, 1, 2, 3, 4, 5};
	std::vector<int> face_list;
	if (rotation == "x")
	{
		face_list = {5, 4, 2, 3, 0, 1};
	}
	else if (rotation == "x2" || rotation == "x2'")
	{
		face_list = {1, 0, 2, 3, 5, 4};
	}
	else if (rotation == "x'")
	{
		face_list = {4, 5, 2, 3, 1, 0};
	}
	else if (rotation == "y")
	{
		face_list = {0, 1, 5, 4, 2, 3};
	}
	else if (rotation == "y2" || rotation == "y2'")
	{
		face_list = {0, 1, 3, 2, 5, 4};
	}
	else if (rotation == "y'")
	{
		face_list = {0, 1, 4, 5, 3, 2};
	}
	else if (rotation == "z")
	{
		face_list = {3, 2, 0, 1, 4, 5};
	}
	else if (rotation == "z2" || rotation == "z2'")
	{
		face_list = {1, 0, 3, 2, 4, 5};
	}
	else if (rotation == "z'")
	{
		face_list = {2, 3, 1, 0, 4, 5};
	}
	for (size_t i = 0; i < alg.size(); ++i)
	{
		alg[i] = 3 * face_list[alg[i] / 3] + alg[i] % 3;
	}
	return alg;
}

std::vector<int> AlgRotation(std::vector<int> &alg, std::string &rotation_algString)
{
	std::istringstream iss(rotation_algString);
	std::string rot;
	while (iss >> rot)
	{
		alg = AlgConvertRotation(alg, rot);
	}
	return alg;
}

std::string ConvertScramble(std::string str)
{
	std::string result1 = "";
	std::string result2 = "";
	std::string rotation = "";
	std::istringstream iss(str);
	std::string name;
	std::vector<int> tmp_alg, tmp_alg2;
	while (iss >> name)
	{
		if (move_convert.count(name) > 0)
		{
			result1 += move_convert[name] + " ";
		}
		else if (rotation_reverse.count(name) > 0)
		{
			result1 += name + " ";
		}
	}
	std::istringstream iss2(result1);
	while (iss2 >> name)
	{
		if (move_convert.count(name) > 0)
		{
			result2 += name + " ";
		}
		else if (rotation_reverse.count(name) > 0)
		{
			tmp_alg = StringToAlg(result2);
			tmp_alg2 = AlgRotation(tmp_alg, name);
			result2 = AlgToString(tmp_alg2);
			rotation += name + " ";
		}
	}
	return result2 + "," + rotation;
}

struct State
{
	std::vector<int> sc;

	State(std::vector<int> arg_sc = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53}) : sc(arg_sc) {}

	void apply_move(const State &move)
	{
		std::vector<int> new_sc(54);
		for (int i = 0; i < 54; ++i)
		{
			new_sc[i] = sc[move.sc[i]];
		}
		sc = std::move(new_sc);
	}
};

std::string StateToInput(const State &state)
{
	std::vector<int> sc = state.sc;
	std::string input = "";
	for (int i : sc)
	{
		if (i < 9)
		{
			input += "U";
		}
		else if (i < 18)
		{
			input += "R";
		}
		else if (i < 27)
		{
			input += "F";
		}
		else if (i < 36)
		{
			input += "D";
		}
		else if (i < 45)
		{
			input += "L";
		}
		else
		{
			input += "B";
		}
	}
	return input;
}

std::unordered_map<std::string, State> moves = {
	{"U", State({6, 3, 0, 7, 4, 1, 8, 5, 2, 45, 46, 47, 12, 13, 14, 15, 16, 17, 9, 10, 11, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 18, 19, 20, 39, 40, 41, 42, 43, 44, 36, 37, 38, 48, 49, 50, 51, 52, 53})},
	{"U2", State({8, 7, 6, 5, 4, 3, 2, 1, 0, 36, 37, 38, 12, 13, 14, 15, 16, 17, 45, 46, 47, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 9, 10, 11, 39, 40, 41, 42, 43, 44, 18, 19, 20, 48, 49, 50, 51, 52, 53})},
	{"U'", State({2, 5, 8, 1, 4, 7, 0, 3, 6, 18, 19, 20, 12, 13, 14, 15, 16, 17, 36, 37, 38, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 45, 46, 47, 39, 40, 41, 42, 43, 44, 9, 10, 11, 48, 49, 50, 51, 52, 53})},
	{"D", State({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 24, 25, 26, 18, 19, 20, 21, 22, 23, 42, 43, 44, 33, 30, 27, 34, 31, 28, 35, 32, 29, 36, 37, 38, 39, 40, 41, 51, 52, 53, 45, 46, 47, 48, 49, 50, 15, 16, 17})},
	{"D2", State({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 42, 43, 44, 18, 19, 20, 21, 22, 23, 51, 52, 53, 35, 34, 33, 32, 31, 30, 29, 28, 27, 36, 37, 38, 39, 40, 41, 15, 16, 17, 45, 46, 47, 48, 49, 50, 24, 25, 26})},
	{"D'", State({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 51, 52, 53, 18, 19, 20, 21, 22, 23, 15, 16, 17, 29, 32, 35, 28, 31, 34, 27, 30, 33, 36, 37, 38, 39, 40, 41, 24, 25, 26, 45, 46, 47, 48, 49, 50, 42, 43, 44})},
	{"L", State({53, 1, 2, 50, 4, 5, 47, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 19, 20, 3, 22, 23, 6, 25, 26, 18, 28, 29, 21, 31, 32, 24, 34, 35, 42, 39, 36, 43, 40, 37, 44, 41, 38, 45, 46, 33, 48, 49, 30, 51, 52, 27})},
	{"L2", State({27, 1, 2, 30, 4, 5, 33, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 53, 19, 20, 50, 22, 23, 47, 25, 26, 0, 28, 29, 3, 31, 32, 6, 34, 35, 44, 43, 42, 41, 40, 39, 38, 37, 36, 45, 46, 24, 48, 49, 21, 51, 52, 18})},
	{"L'", State({18, 1, 2, 21, 4, 5, 24, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 27, 19, 20, 30, 22, 23, 33, 25, 26, 53, 28, 29, 50, 31, 32, 47, 34, 35, 38, 41, 44, 37, 40, 43, 36, 39, 42, 45, 46, 6, 48, 49, 3, 51, 52, 0})},
	{"R", State({0, 1, 20, 3, 4, 23, 6, 7, 26, 15, 12, 9, 16, 13, 10, 17, 14, 11, 18, 19, 29, 21, 22, 32, 24, 25, 35, 27, 28, 51, 30, 31, 48, 33, 34, 45, 36, 37, 38, 39, 40, 41, 42, 43, 44, 8, 46, 47, 5, 49, 50, 2, 52, 53})},
	{"R2", State({0, 1, 29, 3, 4, 32, 6, 7, 35, 17, 16, 15, 14, 13, 12, 11, 10, 9, 18, 19, 51, 21, 22, 48, 24, 25, 45, 27, 28, 2, 30, 31, 5, 33, 34, 8, 36, 37, 38, 39, 40, 41, 42, 43, 44, 26, 46, 47, 23, 49, 50, 20, 52, 53})},
	{"R'", State({0, 1, 51, 3, 4, 48, 6, 7, 45, 11, 14, 17, 10, 13, 16, 9, 12, 15, 18, 19, 2, 21, 22, 5, 24, 25, 8, 27, 28, 20, 30, 31, 23, 33, 34, 26, 36, 37, 38, 39, 40, 41, 42, 43, 44, 35, 46, 47, 32, 49, 50, 29, 52, 53})},
	{"F", State({0, 1, 2, 3, 4, 5, 44, 41, 38, 6, 10, 11, 7, 13, 14, 8, 16, 17, 24, 21, 18, 25, 22, 19, 26, 23, 20, 15, 12, 9, 30, 31, 32, 33, 34, 35, 36, 37, 27, 39, 40, 28, 42, 43, 29, 45, 46, 47, 48, 49, 50, 51, 52, 53})},
	{"F2", State({0, 1, 2, 3, 4, 5, 29, 28, 27, 44, 10, 11, 41, 13, 14, 38, 16, 17, 26, 25, 24, 23, 22, 21, 20, 19, 18, 8, 7, 6, 30, 31, 32, 33, 34, 35, 36, 37, 15, 39, 40, 12, 42, 43, 9, 45, 46, 47, 48, 49, 50, 51, 52, 53})},
	{"F'", State({0, 1, 2, 3, 4, 5, 9, 12, 15, 29, 10, 11, 28, 13, 14, 27, 16, 17, 20, 23, 26, 19, 22, 25, 18, 21, 24, 38, 41, 44, 30, 31, 32, 33, 34, 35, 36, 37, 8, 39, 40, 7, 42, 43, 6, 45, 46, 47, 48, 49, 50, 51, 52, 53})},
	{"B", State({11, 14, 17, 3, 4, 5, 6, 7, 8, 9, 10, 35, 12, 13, 34, 15, 16, 33, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 36, 39, 42, 2, 37, 38, 1, 40, 41, 0, 43, 44, 51, 48, 45, 52, 49, 46, 53, 50, 47})},
	{"B2", State({35, 34, 33, 3, 4, 5, 6, 7, 8, 9, 10, 42, 12, 13, 39, 15, 16, 36, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 2, 1, 0, 17, 37, 38, 14, 40, 41, 11, 43, 44, 53, 52, 51, 50, 49, 48, 47, 46, 45})},
	{"B'", State({42, 39, 36, 3, 4, 5, 6, 7, 8, 9, 10, 0, 12, 13, 1, 15, 16, 2, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 17, 14, 11, 33, 37, 38, 34, 40, 41, 35, 43, 44, 47, 50, 53, 46, 49, 52, 45, 48, 51})}};

std::string ScrambleToState(std::string scramble)
{
	std::vector<std::string> faces;
	for (const auto &pair : moves)
	{
		faces.emplace_back(pair.first);
	}
	State state;
	std::string name;
	std::istringstream iss(scramble);
	while (iss >> name)
	{
		if (!name.empty())
		{
			state.apply_move(moves[name]);
		}
	}
	std::string output = StateToInput(state);
	return output;
}

std::unordered_map<std::string, std::vector<int>> rotations_edge = {
	{"x", {5, 4, 20, 21, 13, 12, 22, 23, 1, 0, 16, 17, 9, 8, 18, 19, 2, 3, 6, 7, 10, 11, 14, 15}},
	{"x2", {12, 13, 10, 11, 8, 9, 14, 15, 4, 5, 2, 3, 0, 1, 6, 7, 20, 21, 22, 23, 16, 17, 18, 19}},
	{"x2'", {12, 13, 10, 11, 8, 9, 14, 15, 4, 5, 2, 3, 0, 1, 6, 7, 20, 21, 22, 23, 16, 17, 18, 19}},
	{"x'", {9, 8, 16, 17, 1, 0, 18, 19, 13, 12, 20, 21, 5, 4, 22, 23, 10, 11, 14, 15, 2, 3, 6, 7}},
	{"y", {6, 7, 0, 1, 2, 3, 4, 5, 14, 15, 8, 9, 10, 11, 12, 13, 19, 18, 23, 22, 17, 16, 21, 20}},
	{"y2", {4, 5, 6, 7, 0, 1, 2, 3, 12, 13, 14, 15, 8, 9, 10, 11, 22, 23, 20, 21, 18, 19, 16, 17}},
	{"y2'", {4, 5, 6, 7, 0, 1, 2, 3, 12, 13, 14, 15, 8, 9, 10, 11, 22, 23, 20, 21, 18, 19, 16, 17}},
	{"y'", {2, 3, 4, 5, 6, 7, 0, 1, 10, 11, 12, 13, 14, 15, 8, 9, 21, 20, 17, 16, 23, 22, 19, 18}},
	{"z", {17, 16, 11, 10, 21, 20, 3, 2, 19, 18, 15, 14, 23, 22, 7, 6, 9, 8, 1, 0, 13, 12, 5, 4}},
	{"z2", {8, 9, 14, 15, 12, 13, 10, 11, 0, 1, 6, 7, 4, 5, 2, 3, 18, 19, 16, 17, 22, 23, 20, 21}},
	{"z2'", {8, 9, 14, 15, 12, 13, 10, 11, 0, 1, 6, 7, 4, 5, 2, 3, 18, 19, 16, 17, 22, 23, 20, 21}},
	{"z'", {19, 18, 7, 6, 23, 22, 15, 14, 17, 16, 3, 2, 21, 20, 11, 10, 1, 0, 9, 8, 5, 4, 13, 12}}};

std::unordered_map<std::string, std::vector<int>> rotations_corner = {
	{"x", {5, 3, 4, 22, 23, 21, 20, 18, 19, 7, 8, 6, 1, 2, 0, 11, 9, 10, 16, 17, 15, 14, 12, 13}},
	{"x2", {21, 22, 23, 12, 13, 14, 15, 16, 17, 18, 19, 20, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2}},
	{"x2'", {21, 22, 23, 12, 13, 14, 15, 16, 17, 18, 19, 20, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2}},
	{"x'", {14, 12, 13, 1, 2, 0, 11, 9, 10, 16, 17, 15, 22, 23, 21, 20, 18, 19, 7, 8, 6, 5, 3, 4}},
	{"y", {9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 17, 18, 19, 20, 21, 22, 23, 12, 13, 14}},
	{"y2", {6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 18, 19, 20, 21, 22, 23, 12, 13, 14, 15, 16, 17}},
	{"y2'", {6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 18, 19, 20, 21, 22, 23, 12, 13, 14, 15, 16, 17}},
	{"y'", {3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 21, 22, 23, 12, 13, 14, 15, 16, 17, 18, 19, 20}},
	{"z", {13, 14, 12, 23, 21, 22, 4, 5, 3, 2, 0, 1, 17, 15, 16, 10, 11, 9, 8, 6, 7, 19, 20, 18}},
	{"z2", {15, 16, 17, 18, 19, 20, 21, 22, 23, 12, 13, 14, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8}},
	{"z2'", {15, 16, 17, 18, 19, 20, 21, 22, 23, 12, 13, 14, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8}},
	{"z'", {10, 11, 9, 8, 6, 7, 19, 20, 18, 17, 15, 16, 2, 0, 1, 13, 14, 12, 23, 21, 22, 4, 5, 3}}};

struct mask
{
	std::string e_mask;
	std::string c_mask;
	mask(std::string arg_e_mask = std::string(24, '-'), std::string arg_c_mask = std::string(24, '-')) : e_mask(arg_e_mask), c_mask(arg_c_mask) {}

	void apply_rotation(std::vector<int> &rotation_e, std::vector<int> &rotation_c)
	{
		std::string new_e_mask(24, '-');
		std::string new_c_mask(24, '-');
		for (int i = 0; i < 24; ++i)
		{
			new_e_mask[i] = e_mask[rotation_e[i]];
			new_c_mask[i] = c_mask[rotation_c[i]];
		}
		e_mask = new_e_mask;
		c_mask = new_c_mask;
	}
};

std::vector<std::string> maskRotation(std::string &arg_e_mask, std::string &arg_c_mask, std::string &rotation_alg)
{
	mask m(arg_e_mask, arg_c_mask);
	std::string rotation_alg_reversed = ReverseScramble(rotation_alg);
	std::istringstream iss(rotation_alg_reversed);
	std::string name;
	while (iss >> name)
	{
		if (!name.empty())
		{
			m.apply_rotation(rotations_edge[rotation_reverse[name]], rotations_corner[rotation_reverse[name]]);
		}
	}
	return {m.e_mask, m.c_mask};
}

std::string convertMask(std::string center, std::string input_e, std::string input_c, std::string rotation_alg)
{
	// de, ble, bre, fre, fle, lle
	// blc, brc, frc, flc, llc
	std::string input_e_tmp = input_e;
	input_e[1] = input_e_tmp[3];
	input_e[2] = input_e_tmp[4];
	input_e[3] = input_e_tmp[2];
	input_e[4] = input_e_tmp[1];
	std::string input_c_tmp = input_c;
	input_c[0] = input_c_tmp[2];
	input_c[1] = input_c_tmp[3];
	input_c[2] = input_c_tmp[0];
	input_c[3] = input_c_tmp[1];
	std::string center_mask(6, 'I');
	std::string e_mask(24, 'I');
	std::string c_mask(24, 'I');
	std::fill(center_mask.begin(), center_mask.end(), center[0]);
	if (input_e[0] != 'I')
	{
		for (int i = 8; i <= 14; i += 2)
		{
			e_mask[i] = input_e[0];
			if (input_e[0] != '?')
			{
				e_mask[i + 1] = input_e[0];
			}
		}
	}
	for (int i = 1; i <= 4; ++i)
	{
		if (input_e[i] != 'I')
		{
			e_mask[14 + 2 * i] = input_e[i];
			if (input_e[i] != '?')
			{
				e_mask[15 + 2 * i] = input_e[i];
			}
		}
	}
	if (input_e[5] != 'I')
	{
		for (int i = 0; i <= 6; i += 2)
		{
			e_mask[i] = input_e[5];
			if (input_e[5] != '?')
			{
				e_mask[i + 1] = input_e[5];
			}
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		if (input_c[i] != 'I')
		{
			c_mask[12 + 3 * i] = input_c[i];
			if (input_c[i] != '?')
			{
				c_mask[13 + 3 * i] = input_c[i];
				c_mask[14 + 3 * i] = input_c[i];
			}
		}
	}
	if (input_c[4] != 'I')
	{
		for (int i = 0; i <= 9; i += 3)
		{
			c_mask[i] = input_c[4];
			if (input_c[4] != '?')
			{
				c_mask[i + 1] = input_c[4];
				c_mask[i + 2] = input_c[4];
			}
		}
	}
	std::vector results = maskRotation(e_mask, c_mask, rotation_alg);
	return results[0] + results[1] + center_mask;
}

EMSCRIPTEN_BINDINGS(my_module)
{
	emscripten::function("scr_mirror", &MirrorScramble);
	emscripten::function("scr_reverse", &ReverseScramble);
	emscripten::function("scr_converter", &ConvertScramble);
	emscripten::function("ScrambleToState", &ScrambleToState);
	emscripten::function("convertMask", &convertMask);
}