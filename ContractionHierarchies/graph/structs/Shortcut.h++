//
// Created by Luca Massei on 9/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_SHORTCUT_H
#define SHORTESTPATHALGORITHMSCPP_SHORTCUT_H

struct Shortcut {
    int from;
    int to;
    int cost;
    int contracted;
};

typedef std::vector<Shortcut> Shortcuts;

#endif //SHORTESTPATHALGORITHMSCPP_SHORTCUT_H
