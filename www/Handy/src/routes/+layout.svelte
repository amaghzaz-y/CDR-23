<script>
	import {
		Content,
		Header,
		HeaderGlobalAction,
		HeaderUtilities,
	} from "carbon-components-svelte";
	import { Home, Settings, ChartStepper } from "carbon-icons-svelte";
	import { goto } from "$app/navigation";
	import "carbon-components-svelte/css/g100.css";
</script>

<Header company="UNIMAKERS" platformName="HandyMan">
	<HeaderUtilities>
		<HeaderGlobalAction
			icon={Settings}
			on:click={() => {
				goto("/settings");
			}}
		/>
		<HeaderGlobalAction
			icon={Home}
			on:click={() => {
				goto("/");
			}}
		/>
		<HeaderGlobalAction
			icon={ChartStepper}
			on:click={() => {
				goto("/stepgen");
			}}
		/>
	</HeaderUtilities>
</Header>

<Content style="padding: 0;">
	<slot />
</Content>
