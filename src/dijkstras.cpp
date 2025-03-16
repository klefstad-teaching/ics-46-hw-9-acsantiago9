#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous) {
	int length = G.numVertices;
	vector<bool> visited(length, false);
	vector<int> distances(length, INF);
	previous.resize(length, -1);

	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(source, 0));
	distances[source] = 0;

	while(!pq.empty()) {
		pair<int, int> curr = pq.top();
		pq.pop();

		if (!visited[curr.first]) {
			
			visited[curr.first] = true;
			for (Edge e: G[curr.first]) {
				
				int dest = e.dst;
				int new_distance = distances[e.src] + e.weight;
				
				if (new_distance < distances[dest]) {
					distances[dest] = new_distance;
					previous[dest] = e.src;
					pq.push(make_pair(dest, new_distance));
				}
			}
		}
	}
	return distances;
}

vector<int> extract_shortest_path(const vector<int> &distances, const vector<int> &previous, int destination) {
	int total = distances[destination];
	stack<int> extract;
	vector<int> path;
	while (destination != -1) {
		extract.push(destination);
		int next = previous[destination];
		destination = next;
	}
	while (!extract.empty()) {
		path.push_back(extract.top());
		extract.pop();
	}
	return path;
}

void print_path(const vector<int> &v, int total) {
	int length = v.size();
	for (int i: v) {
		cout << i << " ";
	}
	cout << endl;
	cout << "Total cost is " << total << endl;
}