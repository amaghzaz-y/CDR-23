<script>
	import ConnectionChecker from "$lib/components/ConnectionChecker.svelte";
	import HostIp from "$lib/components/HostIP.svelte";
	import { Column, Grid, Row } from "carbon-components-svelte";
</script>

<Grid>
	<Row style={"margin-block: 1rem"}>
		<Column>
			<ConnectionChecker />
		</Column>
	</Row>
	<Row>
		<Column>
			<HostIp />
		</Column>
	</Row>
</Grid>
