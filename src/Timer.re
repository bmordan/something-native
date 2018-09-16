open BsReactNative;

type state = {
    duration: option(int),
    timer: option(int)
};

type action =
  | Start(int)
  | Dec(int)
  | Stop;

module Styles = {
    open Style;

    let button = style([marginTop(Pt(30.))]);
    let text = style([color(String("#fff")), fontSize(Float(22.)), marginTop(Pt(30.))]);
};

let component = ReasonReact.reducerComponent("Timer");

let make = _children => {
  ...component,
  initialState: () => {
    duration: None,
    timer: None
  },
  reducer: (action, state) => {
    switch(action) {
    | Start(duration) => ReasonReact.Update({timer: Some(duration), duration: Some(duration)})
    | Dec(timer) => ReasonReact.NoUpdate
    | Stop => ReasonReact.Update({...state, timer: None})
    };
  },
  render: ({state, send}) =>
    <View>
        (
            switch (state.timer) {
            | Some(time) =>
                <View style=Styles.button>
                    <Button title="Cancel" onPress=(_evt => send(Stop)) color="#DC143C" />
                    <Text style=Styles.text>(ReasonReact.string(string_of_int(time)))</Text>
                </View>
            | None =>
              <View style=Styles.button>
                <Button title="Start" onPress=(_evt => send(Start(10))) color="#DC143C" />
              </View>
            }
        )
    </View>
};
