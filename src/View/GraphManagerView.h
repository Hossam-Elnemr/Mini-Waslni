#ifndef GRAPH_MANAGER_VIEW_H
#define GRAPH_MANAGER_VIEW_H
#include "../Model/Headers/Globals.h"
#include "../Helpers/Tools.h"
namespace View{
	//This class To handle the graph operations.
	class GraphManagerView {
	public:
		GraphManagerView() = default;

		void getGraphInfo();
		void getCityInfo();
		void getEdgeInfo();
		void showGraph();
		void showPath();
		pair<string, string> getPathFindingInfo();
		
		~GraphManagerView();
	};

}


#endif