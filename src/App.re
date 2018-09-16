open BsReactNative;

/* here we define some styles */
module Styles = {
  open Style;

  let container =
    style([
      flex(1.),
      justifyContent(Center),
      alignItems(Center),
      backgroundColor(String("tomato")),
    ]);

  let text = style([color(String("#fff")), fontSize(Float(24.))]);

  let button = style([marginTop(Pt(30.))]);
};

module Main = {
  let component = ReasonReact.statelessComponent("Main");

  let make = _children => {
    ...component,
    render: _self =>
      <View style=Styles.container>
        <Text style=Styles.text>
          (ReasonReact.string("Something to meditate on"))
        </Text>
        <View style=Styles.button>
          <Button title="Start" onPress={() => {Js.log("start the timer")}} color="#CD5C5C"/>
        </View>
      </View>,
  };
};

let app = () => <Main />;