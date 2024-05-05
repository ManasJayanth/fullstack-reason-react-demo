[@react.component]
let make = (~children=?) => {
  <div>
    {switch (children) {
     | None => React.null
     | Some(c) => c
     }}
  </div>;
};
