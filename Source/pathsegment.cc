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
}

void Utilities::PathSegment::set_source(Point source) {
    this->source = source;
    update_length();
}

void Utilities::PathSegment::set_sink(Point sink) {
    this->sink = sink;
    update_length();
}

"pathsegment.cc" 101L, 2519C                                                                                                                                                                                                       97,4          Bot
