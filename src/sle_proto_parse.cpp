bool isCornerPresent(std::string str, std::string pattern)
{
	if (str.find(pattern) != std::string::npos) {
		return true;
	}
	else {
		return false;
	}

	return false;
}



std::vector<int> parsecircle(char* buffer) {
	int i, startindex, endindex, r_startindex, r_endindex, c_startindex, c_endindex, number, radius;
	bool end = false;
	std::vector<int> point;
	std::string wholenumber;

	std::string str = buffer;
	//std::cout << "\nDrawing a circle: " << str << "\n\n";

	startindex = 10;
	i = startindex;

	while (end == false) {
		char currentchar = buffer[i];
		if (currentchar == '}') {
			////std::cout << "Found the end: " << i;
			endindex = i;
			end = true;
		}
		i = ++i;
	}

	end = false;
	r_startindex = startindex + 2;
	i = r_startindex;
	while (end == false) {
		char currentchar = buffer[i];
		if (currentchar == ';') {
			////std::cout << "Found the end: " << i;
			r_endindex = i;
			end = true;
		}
		i = ++i;
	}

	end = false;

	for (int i = r_startindex; i < r_endindex + 1; ++i)
	{
		if (buffer[i] == ';') {
			//std::cout << "Circle stoi-1 arg: [" << wholenumber << "]\n\n";
			number = std::stoi(wholenumber);
			radius = number;
			wholenumber = "";

		} else {
			wholenumber += buffer[i];

		}
	}

	c_startindex = r_endindex + 3;

	end = false;
	i = c_startindex;

	while (end == false) {
		if (buffer[i] == '}') {
			c_endindex = i - 1;
			////std::cout << "\nfound the end: " << c_endindex;
			end = true;
		}
		i += 1;
	}

	end = false;



	for (int i = c_startindex; i < c_endindex + 1; ++i)
	{
		if (buffer[i] == ',' || buffer[i] == ';') {
			////std::cout << "\nNumber: " << wholenumber << "\n";
			//std::cout << "Circle stoi-2 arg: [" << wholenumber << "]\n\n";
			number = std::stoi(wholenumber);
			wholenumber = "";
			point.push_back(number);
		} else {
			wholenumber += buffer[i];
		}
	}


	point.push_back(radius);
	//std::cout << "\nRadius: " << point[2] << "\n";
	//std::cout << "\nX: " << point[0] << "  Y: " << point[1];
	return point;
	/*for (int i = c_startindex; i < c_endindex; ++i)
	{
		//std::cout << buffer[i] << "\n";
	}*/
}


std::vector<std::vector<int> > parsepolygon(char* buffer) {
	int i, startindex, endindex, c_startindex, c_endindex, number;
	bool end = false;
	std::vector<std::vector<int> > points;
	std::vector<int> point;
	std::string wholenumber;

	std::string str = buffer;
	//std::cout << "\nDrawing a polygon: " << str << "\n\n";

	startindex = 11;
	i = startindex;
	endindex;

	while (end == false) {
		char currentchar = buffer[i];
		if (currentchar == '}') {
			////std::cout << "Found the end: " << i;
			endindex = i;
			end = true;
		}
		i = ++i;
	}

	end = false;
	c_startindex = startindex + 2;
	i = c_startindex;
	while (end == false) {
		char currentchar = buffer[i];
		if (currentchar == ';') {
			////std::cout << "Found the end: " << i;
			c_endindex = i;
			end = true;
		}
		i = ++i;
	}

	end = false;

	for (int i = c_startindex; i < c_endindex + 1; ++i)
	{
		if (buffer[i] == ',') {
			//std::cout << "Poly stoi-1 arg: [" << wholenumber << "]\n\n";
			number = std::stoi(wholenumber);
			point.push_back(number);
			wholenumber = "";

		} else if (buffer[i] == '|' || buffer[i] == ';') {
			//std::cout << "Poly stoi-2 arg: [" << wholenumber << "]\n\n";
			number = std::stoi(wholenumber);
			point.push_back(number);
			points.push_back(point);
			wholenumber = "";
			point.clear();
		} else {
			wholenumber += buffer[i];

		}


	}

	for (int i = 0; i < points.size(); ++i)
	{
		point = points[i];
		//std::cout << "\nX: " << point[0] << "  Y: " << point[1];
	}

	return points;
	/*for (int i = c_startindex; i < c_endindex; ++i)
	{
		//std::cout << buffer[i] << "\n";
	}*/
}


void parsedot(char* buffer) {
	std::string str = buffer;
	//std::cout << "\nDrawing a dot: " << str << "\n\n";
}


void parseline(char* buffer) {
	std::string str = buffer;
	//std::cout << "\nDrawing a line: " << str << "\n\n";
}

std::string parse(char* buffer) {

	std::string longstring;
	std::string str = buffer;
	std::string endpattern = "@@@";
	std::string type;


	if (isCornerPresent(str, endpattern)) {
		//std::cout << "\nseems like we reached the end of buffer: " << str << "\n\n";
		//return longstring;
	}

	
	if (buffer[0] == '@') {
		if (buffer[2] == 'p' && buffer[8] == 'n') {
			std::vector<std::vector<int> > dots = parsepolygon(buffer);
			type = "polygon";
			std::vector<std::vector<int> > points = polygon(dots);

			for (int i = 0; i < points.size(); ++i)
			{
				std::string open_bracket = "[";
				std::vector<int >  point = points[i];
				int x = point[0];
				int y = point[1];
				//std::cout << "[" << x << "," << y << "],";
				//longstring += "[" + x + "," + y + "],";


				//std::string x = std::to_string(point[0]);
				//std::string y = std::to_string(point[1]);

				std::string a = "[";
				std::string b = "&";
				std::string c = "]";
				std::string d = ",";

				longstring += a;
				longstring += std::to_string(point[0]);
				longstring += b;
				longstring += std::to_string(point[1]);
				longstring += c;
				longstring += d;

			}
			return longstring;
		} else if (buffer[2] == 'c' && buffer[7] == 'e') {
			std::vector<int> point = parsecircle(buffer);
			type = "circle";


			int radius = point[2];
			int xpos = point[0];
			int ypos = point[1];

			//std::cout << "Radius: "<< radius << "  X: "<< xpos << "  Y: "<< ypos;

			std::vector<std::vector<int> > lines4 = circle(xpos, ypos, radius);
			for (int i = 0; i < lines4.size(); ++i)
			{
				std::vector<int > point = lines4[i];
				std::string x = std::to_string(point[0]);
				std::string y = std::to_string(point[1]);

				std::string a = "[";
				std::string b = "&";
				std::string c = "]";
				std::string d = ",";

				longstring += a;
				longstring += std::to_string(point[0]);
				longstring += b;
				longstring += std::to_string(point[1]);
				longstring += c;
				longstring += d;
				//std::cout << "[" << point[0] << "," << point[1] << "],";

			}
			return longstring;

		} else if (buffer[2] == 'l' && buffer[5] == 'e') {
			parseline(buffer);
		} else if (buffer[2] == 'd' && buffer[4] == 't') {
			parsedot(buffer);
		} else {
			//std::cout << "\nUnrecognised Argument\n\n";
		}

	} else if (buffer[0] == '#') {
		//std::cout << "\nScreen settings not implemented yet: " << str << "\n\n";
		return longstring;
	}
	return longstring;

}


/*

    for (int i = 0; buffer[i] != '\0'; i++){
      //std::cout << "\nc:" << buffer[i] << "\n";
    }


*/