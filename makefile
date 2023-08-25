simcity: main.o City.o Commercial.o Industrial.o pollution.o Residential.o Airport.o PlaneCrash.o
	g++ -o  simcity main.o City.o Commercial.o Industrial.o pollution.o Residential.o Airport.o PlaneCrash.o

main.o: main.cpp
	g++ -c main.cpp

City.o: City.cpp City.h 
	g++ -c City.cpp City.h

Commercial.o: Commercial.cpp Commercial.h
	g++ -c Commercial.cpp Commercial.h

Industrial.o: Industrial.cpp Industrial.h
	g++ -c Industrial.cpp Industrial.h

pollution.o: pollution.cpp pollution.h
	g++ -c pollution.cpp pollution.h

Residential.o: Residential.cpp Residential.h
	g++ -c Residential.cpp Residential.h

Airport.o: Airport.cpp Airport.h
	g++ -c Airport.cpp Airport.h

PlaneCrash.o: PlaneCrash.cpp PlaneCrash.h
	g++ -c PlaneCrash.cpp PlaneCrash.h
