let useStateValue = (initial: 'a) => {
  React.useReducer((_ignored, newState) => newState, initial);
};

/* module ExternalLinkIcon = {
     [@react.component]
     let make = (~children) => {
       <svg
         xmlns="http://www.w3.org/2000/svg"
         viewBox="0 0 24 24"
         width="24px"
         height="24px">
         <path
           d="M 5 3 C 3.9069372 3 3 3.9069372 3 5 L 3 19 C 3 20.093063 3.9069372 21 5 21 L 19 21 C 20.093063 21 21 20.093063 21 19 L 21 12 L 19 12 L 19 19 L 5 19 L 5 5 L 12 5 L 12 3 L 5 3 z M 14 3 L 14 5 L 17.585938 5 L 8.2929688 14.292969 L 9.7070312 15.707031 L 19 6.4140625 L 19 10 L 21 10 L 21 3 L 14 3 z"
         />
       </svg>;
     };
   }; */

module ExternalLinkIcon = {
  [@react.component]
  let make = () => {
    <span> {React.string({js|🔗|js})} </span>;
  };
};

module Panel = {
  [@react.component]
  let make = (~children) => {
    <div> children </div>;
  };
};

module ShrinkerText = {
  [@react.component]
  let make = (~children) => {
    let first = children.[0] |> String.make(1);
    let rest = String.sub(children, 1, String.length(children) - 1);

    <>
      <span> {React.string(first)} </span>
      <span> {React.string(rest)} </span>
    </>;
  };
};

module Logo = {
  [@react.component]
  let make = () => {
    <p> <ShrinkerText> "ahrefs" </ShrinkerText> </p>;
  };
};

module Dropdown = {
  module Trigger = {
    [@react.component]
    let make = (~onClick) => {
      <div onClick> {React.string("More tools")} </div>;
    };
  };

  /* let useClickOutside = (domRef, callback) => {
       open Webapi.Dom;
       let onClickHandler = event => {
         MouseEvent.stopPropagation(event);
         let target = MouseEvent.target(event);
         let targetElement = EventTarget.unsafeAsElement(target);
         let targetIsOutsideOverlayTrigger =
           switch (domRef |> Js.Nullable.toOption) {
           | Some(ref_) => !Element.contains(targetElement, ref_)
           | None => false
           };

         if (targetIsOutsideOverlayTrigger) {
           callback();
         };
       };

       React.useEffect2(
         () => {
           Document.addMouseDownEventListener(onClickHandler, document);
           Some(
             () =>
               Document.removeMouseDownEventListener(onClickHandler, document),
           );
         },
         (onClick, domRef.React.current),
       );
     }; */

  [@react.component]
  let make = (~items, ~onClick) => {
    let (isOpen, setIsOpen) = useStateValue(false);
    let _triggerRef = React.useRef(Js.Nullable.null);

    /* useClickOutside(triggerRef, () =>
         if (isOpen) {
           setIsOpen(false);
         }
       ); */

    <div>
      <Trigger onClick={_e => setIsOpen(!isOpen)} />
      {isOpen
         ? {
           <div>
             {React.array(
                Belt.Array.mapWithIndex(items, (key, item) =>
                  <div key={Int.to_string(key)}>
                    <span onClick={_e => onClick(item)}>
                      {React.string(item)}
                    </span>
                  </div>
                ),
              )}
           </div>;
         }
         : React.null}
    </div>;
  };
};

module Menu = {
  /* let useOnResize = () => {
       React.useEffect1(
         () => {
           open Webapi.Dom;
           let windowAsTarget = Window.asEventTarget(window);
           let handleResize = _ => setWindowHeight(_ => getWindowHeight());
           EventTarget.addEventListener("resize", handleResize, windowAsTarget);
           Some(
             () =>
               EventTarget.removeEventListener(
                 "resize",
                 handleResize,
                 windowAsTarget,
               ),
           );
         },
         [||],
       );
     }; */

  [@react.component]
  let make = (~navigate: string => unit) => {
    let (tools, _setTools) =
      useStateValue([|
        "Dashboard",
        "Site Explorer",
        "Keywords Explorer",
        "Site Audit",
        "Rank Tracker",
        "Content Explorer",
      |]);

    let (moreTools, _setMoreTools) =
      useStateValue([|
        "Alerts",
        "Ahrefs Rank",
        "Batch Analysis",
        "Link intersect",
        "SEO Toolbar",
        "WordPress Plugin",
        "Ahrefs API",
        "Apps",
      |]);

    let externalLinks = [|"Community", "Academy"|];

    <div>
      {React.array(
         Belt.Array.mapWithIndex(tools, (key, item) =>
           <div key={Int.to_string(key)}>
             <span onClick={_e => navigate(item)}>
               {React.string(item)}
             </span>
           </div>
         ),
       )}
      <Dropdown items=moreTools onClick=navigate />
      <span> {React.string("|")} </span>
      {React.array(
         Belt.Array.mapWithIndex(externalLinks, (key, item) =>
           <div key={Int.to_string(key)}>
             <span onClick={_e => navigate(item)}>
               <Row> {React.string(item)} <ExternalLinkIcon /> </Row>
             </span>
           </div>
         ),
       )}
    </div>;
  };
};

[@react.component]
let make = () => {
  let (currentNavigate, setNavigate) = useStateValue("Dashboard");

  <Root>
    <Panel>
      <Row>
        <Spacer> <Logo /> </Spacer>
        <Menu navigate={to_ => setNavigate(to_) |> ignore} />
      </Row>
      <SubHeader />
    </Panel>
    <div> <Align> <h2> {React.string(currentNavigate)} </h2> </Align> </div>
  </Root>;
};
