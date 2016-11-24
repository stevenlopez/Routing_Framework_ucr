
Utilities::PathSegment::PathSegment(Point source, Point sink):
        source(source.x,source.y),sink(sink.x,sink.y) {
    update_length();
}

Utilities::PathSegment::PathSegment(int p1_x, int p1_y, int p2_x, int p2_y):
        source(p1_x,p1_y),sink(p2_x,p2_y) {
    update_length();
}

Utilities::PathSegment::~PathSegment() {
    /* Empty Destructor */
}

bool Utilities::PathSegment::operator==(const PathSegment& rhs) {
    if(this->source == rhs.source && this->sink == rhs.sink) {
        return true;
    }
    return false;
}

Point Utilities::PathSegment::get_source() {
    return this->source;
}

Point Utilities::PathSegment::get_sink() {
    return this->sink;
}

int Utilities::PathSegment::get_length() {
    return this->length;
}

bool Utilities::PathSegment::contains_points(Point source, Point sink) {
    if(source == this->source && sink == this->sink) {
        return true;
    }
    return false;
}

void Utilities::PathSegment::print_source() {
        cout << "(" << this->source.x << "," << this->source.y << ")";
}
void Utilities::PathSegment::print_sink() {
    cout << "(" << this->sink.x << "," << this->sink.y << ")";
}

void Utilities::PathSegment::print() {
    if(this->sink.x == -10){
            cout << "\n";
    }
    else{
        this->print_sink();
        cout << " -> ";
        this->print_source();
        //print sink to source
    }
                                                                                                                                                                                                                                   49,4          72%
