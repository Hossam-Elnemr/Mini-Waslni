#ifndef GRAPH_MANAGER_VIEW_H
#define GRAPH_MANAGER_VIEW_H

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
		
		~GraphManagerView();
	};

}


#endif