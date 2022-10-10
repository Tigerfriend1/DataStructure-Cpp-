#자료구조 과제3
##simple deque 구현
###front와 back으로 번갈아가며 값을 push할 수 있는 deque를 구현하라.
조건 1. Deque의 초기 생성자는 capacity를 2로 한다.

조건 2. push하여 capacity 보다 많으면 용량을 2배로 늘린다.

조건 3. Deque를 simple (circular가 아님) deque로 구현한다.

조건 4. push_front(), push_back()를 번갈아 가면서 호출하는데 각 10개 이상 호출한다. push_front()에서 index [0]에 데이터가 있으면 용량을 2배로 늘리고  front 시작점을 용량의 1/3 지점으로 이동한다.