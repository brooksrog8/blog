import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import BlogList from './components/BlogList';
import BlogPost from './components/BlogPost';

const App = () => {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<BlogList />} />
        <Route path="/post/:id" element={<BlogPost />} />
      </Routes>
    </Router>
  );
};

export default App;
